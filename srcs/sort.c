//
// Created by peer on 13-11-22.
//
#include <string.h>
#include "flags.h"
#include "t_node.h"
#include "libft.h"
#include "ft_ls.h"

static int case_insensitive_strcmp(const char* lhs, const char* rhs) {
	size_t i = 0;

	if (lhs[0] == '.')
		++lhs;
	if (rhs[0] == '.')
		++rhs;
	while (lhs[i] && rhs[i] && ft_tolower(lhs[i]) == ft_tolower(rhs[i])) {
		i++;
	}
	return (ft_tolower(lhs[i]) - ft_tolower(rhs[i]));
}

static int compare_by_time(struct timespec lhs, struct timespec rhs) {
	if (lhs.tv_sec == rhs.tv_sec)
		return ((int)(lhs.tv_nsec - rhs.tv_nsec));
	else
		return ((int)(lhs.tv_sec - rhs.tv_sec));
}

int	compare_nodes(const void* v_dataObject, const void* v_pivot) {
	const t_node* dataObject = (t_node *)v_dataObject;
	const t_node* pivot = (t_node *)v_pivot;
	int cmp_ret;

	if (g_flags & FLAG_t) {
		cmp_ret = compare_by_time(pivot->statbuf.st_mtim, dataObject->statbuf.st_mtim);
	} else {
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
