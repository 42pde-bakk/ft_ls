//
// Created by peer on 13-11-22.
//
#include <string.h>
#include "flags.h"
#include "t_node.h"
#include "libft.h"
#include "ft_ls.h"

bool	is_a_special_cunt(const char c) {
//	return (c == '.');
	return (c == '.' || c == '_');
}


//   int diff = filevercmp (a->name, b->name);
//  return diff ? diff : strcmp (a->name, b->name);

static int case_insensitive_strcmp(const char* lhs, const char* rhs) {
	size_t lhs_i = 0;
	size_t rhs_i = 0;

	while (lhs[lhs_i] && rhs[rhs_i]) {
		if (is_a_special_cunt(lhs[lhs_i]) || is_a_special_cunt(rhs[rhs_i])) {
			if (is_a_special_cunt(lhs[lhs_i]))
				++lhs_i;
			if (is_a_special_cunt(rhs[rhs_i]))
				++rhs_i;
			continue;
		}
		if (ft_tolower(lhs[lhs_i]) != ft_tolower(rhs[rhs_i])) {
			break ;
		}
		++lhs_i;
		++rhs_i;
	}
	return (ft_tolower(lhs[lhs_i]) - ft_tolower(rhs[rhs_i]));
}

static int compare_by_time(struct timespec lhs, struct timespec rhs) {
	if (lhs.tv_sec == rhs.tv_sec)
		return ((int)(lhs.tv_nsec - rhs.tv_nsec));
	else
		return ((int)(lhs.tv_sec - rhs.tv_sec));
}

// https://github.com/ekg/filevercmp/blob/master/filevercmp.c
int	ft_filevercmp(const char* const s1, const char* const s2) {
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

bool	is_dot_or_double_dot(const char* const str) {
	return (strcmp(str, ".") == 0 || strcmp(str, "..") == 0);
}

int	compare_nodes(const void* v_dataObject, const void* v_pivot) {
	const t_node* dataObject = (t_node *)v_dataObject;
	const t_node* pivot = (t_node *)v_pivot;
	int cmp_ret;

//	filevercmp = ft_filevercmp(dataObject->name, pivot->name);
//	if (filevercmp) {
//		return (filevercmp);
//	}

	if (g_flags & FLAG_t) {
//		cmp_ret = is_dot_or_double_dot(pivot->name) - is_dot_or_double_dot(dataObject->name);
//		if (cmp_ret == 0) {
		cmp_ret = compare_by_time(pivot->statbuf.st_mtim, dataObject->statbuf.st_mtim);
//		}
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
