//
// Created by peer on 19-1-23.
//

#ifndef FT_LS_SORTING_H
#define FT_LS_SORTING_H
#include "t_node.h"

typedef int (*t_func_cmpstrings)(char const*, char const*);

int	sort_on_timestamp(const t_node* dataObject, const t_node* pivot, t_func_cmpstrings strcmpFunc);
int case_insensitive_strcmp(const char* lhs, const char* rhs);

#endif //FT_LS_SORTING_H
