//
// Created by peer on 13-11-22.
//
#include <string.h>
#include "flags.h"
#include "t_node.h"
#include "libft.h"
#include "ft_ls.h"
#include "sorting.h"

// https://github.com/ekg/filevercmp/blob/master/filevercmp.c
int ft_filevercmp(const char* const s1, const char* const s2) {
	if (strcmp(".", s1) == 0)
		return -1;
	if (strcmp(".", s2) == 0)
		return 1;
	if (strcmp("..", s1) == 0)
		return -1;
	if (strcmp("..", s2) == 0)
		return 1;
	return (0);
}

bool is_dot_or_double_dot(const char* const str) {
	return (strcmp(str, ".") == 0 || strcmp(str, "..") == 0);
}

int compare_nodes(const void* v_dataObject, const void* v_pivot) {
	const t_node* dataObject = (t_node*)v_dataObject;
	const t_node* pivot = (t_node*)v_pivot;
	int cmp_ret;

	if (g_flags & FLAG_t) {
		cmp_ret = sort_on_timestamp(dataObject, pivot, &case_insensitive_strcmp);
	} else {
		if (ft_strcmp(dataObject->name, pivot->name) == 0) {
			return (0);
		}
		cmp_ret = case_insensitive_strcmp(dataObject->name, pivot->name);
		if (cmp_ret == 0) {
			cmp_ret = ft_strcmp(pivot->name, dataObject->name);
		}
	}

	if (g_flags & FLAG_r) {
		cmp_ret *= -1;
	}
	return (cmp_ret);
}
