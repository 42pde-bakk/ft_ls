//
// Created by pde-bakk on 1/18/23.
//

#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include "t_node.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// srcs/parsing.c
const char*	get_program_name();
unsigned int parse_flags(char** argv, t_ptrvector* file_vector);

// srcs/sort.c
int	compare_nodes(const void* dataObject, const void* pivot);

// srcs/collect_children_nodes.c
int collect_children_nodes(t_node* ls_obj);

// srcs/symbolic_links.c
char* get_symlink_path(const t_node* dataObj);

typedef struct s_column_sizes {
	int nb_links;
	size_t user;
	size_t group;
	int filesize;
}	t_column_sizes;

#endif //FT_LS_FT_LS_H
