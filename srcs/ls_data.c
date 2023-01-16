//
// Created by peer on 12-11-22.
//
#include "data_obj.h"
#include "libft.h"

t_data* create_new_rootnode(const char* arg) {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);

	stat(arg, &obj->statbuf);
	obj->is_root_node = true;
	obj->name = ft_strdup(arg);
	obj->fullpath = ft_strdup(arg);
	obj->vector = ptrvector_init(16, false);
	return (obj);
}

t_data *create_new_object(const char *prefix, const char* pdirent_name) {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);
	obj->name = ft_strdup(pdirent_name);
	if (!obj->name)
		exit(EXIT_FAILURE);
	obj->fullpath = ft_str3join(prefix, "/", obj->name);
	if (!obj->fullpath)
		exit(EXIT_FAILURE);
	obj->vector = ptrvector_init(16, false);

	ft_bzero(&obj->statbuf, sizeof(obj->statbuf));
	stat(obj->fullpath, &obj->statbuf);

	return (obj);
}

void*	destroy_object(t_data* dataObj) {
	if (dataObj == NULL)
		return (NULL);
	free(dataObj->name);
	free(dataObj->fullpath);
	for (size_t i = 0; i < dataObj->vector->size; i++) {
		destroy_object(dataObj->vector->arr[i]);
	}
	ptrvector_destroy(dataObj->vector);

	free(dataObj);

	return (NULL);
}
