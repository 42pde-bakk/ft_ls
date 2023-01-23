//
// Created by peer on 12-11-22.
//
#include "t_node.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_ls.h"
#include <string.h>
#include <errno.h>


t_node* create_new_rootnode(const char* arg) {
	t_node* obj = ft_calloc(1, sizeof(t_node));

	if (!obj)
		exit(EXIT_FAILURE);

	if ((stat(arg, &obj->statbuf)) == -1) {
		ft_dprintf(STDERR_FILENO, "%s: cannot access '%s': %s\n", get_program_name(), arg, strerror(errno));
		exit(EXIT_FAILURE);
	}
	obj->name = ft_strdup(arg);
	obj->fullpath = ft_strdup(arg);
	if (obj->name == NULL || obj->fullpath == NULL) {
		exit(EXIT_FAILURE);
	}
	if ((obj->vector = ptrvector_init(16, false)) == NULL)
		exit(EXIT_FAILURE);
	return (obj);
}

t_node* create_new_object(const char* prefix, const char* pdirent_name) {
	t_node* obj = ft_calloc(1, sizeof(t_node));

	if (!obj)
		exit(EXIT_FAILURE);
	obj->name = ft_strdup(pdirent_name);
	if (!obj->name)
		exit(EXIT_FAILURE);
	obj->fullpath = ft_str3join(prefix, "/", obj->name);
	if (!obj->fullpath)
		exit(EXIT_FAILURE);
	if ((obj->vector = ptrvector_init(16, false)) == NULL)
		exit(EXIT_FAILURE);

	if ((lstat(obj->fullpath, &obj->statbuf)) == -1) {
		ft_dprintf(STDERR_FILENO, "%s: cannot access '%s': %s\n", get_program_name(), obj->fullpath, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return (obj);
}

void destroy_object(t_node* dataObj) {
	free(dataObj->name);
	free(dataObj->fullpath);
	for (size_t i = 0; i < dataObj->vector->size; i++) {
		destroy_object(dataObj->vector->arr[i]);
	}
	ptrvector_destroy(dataObj->vector);
	free(dataObj);
}
