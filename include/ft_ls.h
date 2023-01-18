//
// Created by pde-bakk on 1/18/23.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include "t_node.h"

typedef int idx_t;


// srcs/parsing.c
unsigned int parse_flags(char** argv, t_ptrvector* file_vector);

// srcs/sort.c
//t_ptrvector_sort_function compare_nodes;
int	compare_nodes(const void* dataObject, const void* pivot);

// srcs/collect_children_nodes.c
void collect_children_nodes(t_node* ls_obj);

// srcs/ft_str3join.c
char* ft_str3join(const char* a, const char* b, const char* c);

// srcs/get_filetype.c
unsigned char get_filetype(const char* name);

// srcs/symbolic_links.c
char* get_symlink_path(const t_node* dataObj);

#endif //FT_LS_FT_LS_H
