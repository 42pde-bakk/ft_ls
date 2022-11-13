//
// Created by peer on 12-11-22.
//
#include "data_obj.h"
#include "flags.h"
#include "libft.h"
#include "ft_printf.h"

t_data *create_new_object_root() {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);
	obj->vector = ptrvector_init(128, false);
	return (obj);
}

t_data *create_new_object(const char *prefix, struct dirent *pdirent) {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);
	if (pdirent) {
		obj->type = pdirent->d_type;
		obj->name = ft_strdup(pdirent->d_name);
		ft_memcpy(&(obj->pDirent), pdirent, sizeof(struct dirent));
	} else {
		obj->type = DT_UNKNOWN;
	}
	if (prefix)
		obj->prefix = ft_strdup(prefix);
	if (obj->prefix && obj->name)
		obj->fullpath = ft_str3join(obj->prefix, "/", obj->name);
	ft_bzero(&obj->buf, sizeof(obj->buf));
	obj->vector = ptrvector_init(128, false);

	return (obj);
}

t_data *create_new_object_of_type(const char *const prefix, const char *const name, unsigned char type, bool go_down_layer) {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);
	obj->type = type;
	if (name)
		obj->name = ft_strdup(name);
	if (prefix)
		obj->prefix = ft_strdup(prefix);
	if (obj->prefix && obj->name)
		obj->fullpath = ft_str3join(obj->prefix, "/", obj->name);
	ft_bzero(&obj->buf, sizeof(obj->buf));
	obj->vector = ptrvector_init(128, false);

	if (go_down_layer && obj->type == DT_DIR) {
		collect_children_nodes(obj);
	}

	return (obj);
}

t_data *create_new_object_blank(char *fullpath, bool go_down_layer) {
	t_data*	obj = ft_calloc(1, sizeof(t_data));

	if (!obj)
		exit(EXIT_FAILURE);
	obj->type = DT_DIR;
	if (fullpath)
		obj->name = ft_strdup(fullpath);
	obj->prefix = NULL;
	if (obj->name)
		obj->fullpath = ft_strdup(obj->name);
	ft_bzero(&obj->buf, sizeof(obj->buf));
	obj->vector = ptrvector_init(128, false);

	if (go_down_layer && obj->type == DT_DIR) {
		collect_children_nodes(obj);
	}
	return (obj);
}

void*	destroy_object(t_data* dataObj) {
	if (dataObj == NULL)
		return (NULL);
	free(dataObj->name);
	free(dataObj->prefix);
	free(dataObj->fullpath);
	for (size_t i = 0; i < dataObj->vector->size; i++) {
		destroy_object(dataObj->vector->arr[i]);
	}
	ptrvector_destroy(dataObj->vector);

	free(dataObj);

	return (NULL);
}

void	print_object(const t_data* dataObj) {
	if (dataObj->vector->size > 1) {
		sort_dataObjects((t_data **)dataObj->vector->arr, dataObj->vector->size);
	}
	bool print_header = false;
	if (dataObj->vector->size) {
		if (g_flags & FLAG_R || (dataObj->parent && dataObj->parent->vector->size > 1)) {
			print_header = true;
		}
		if (print_header)
			ft_printf("%s:\n", dataObj->name);
		for (size_t i = 0; i < dataObj->vector->size; i++) {
			print_object(dataObj->vector->arr[i]);
			if (i != dataObj->vector->size - 1)
				ft_printf("  ");
		}
		if (print_header)
			ft_printf("%c", '\n');
		ft_printf("%c", '\n');
	}
	else if (dataObj->name) {
		ft_printf("%s", dataObj->name);
	}
}
