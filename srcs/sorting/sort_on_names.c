//
// Created by peer on 19-1-23.
//

#include <stddef.h>
#include <stdbool.h>
#include "libft.h"

static bool	is_special_case(const char c) {
	return (c == '.' || c == '_');
}

int case_insensitive_strcmp(const char* lhs, const char* rhs) {
	size_t lhs_i = 0;
	size_t rhs_i = 0;

	while (lhs[lhs_i] && rhs[rhs_i]) {
		if (is_special_case(lhs[lhs_i]) || is_special_case(rhs[rhs_i])) {
			if (is_special_case(lhs[lhs_i]))
				++lhs_i;
			if (is_special_case(rhs[rhs_i]))
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
