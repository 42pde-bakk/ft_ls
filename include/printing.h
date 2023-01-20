//
// Created by pde-bakk on 1/20/23.
//

#ifndef FT_LS_PRINTING_H
#define FT_LS_PRINTING_H
#include <stddef.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct s_column_sizes {
	int nb_links;
	size_t user;
	size_t group;
	int filesize;
}	t_column_sizes;


const char* get_username(const struct stat* statbuf);
const char* get_groupname(const struct stat* statbuf);

t_column_sizes 	get_column_sizes(const t_node* node);
void	print_long_listing_format(const t_node* dataObj, const t_column_sizes* columnSizes);

#endif //FT_LS_PRINTING_H
