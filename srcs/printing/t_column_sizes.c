//
// Created by peer on 19-1-23.
//

#include "ft_ls.h"
#include "libft.h"
#include "printing.h"

static int get_amount_digits(size_t n) {
	int digits = 1;
	while (n > 9) {
		n /= 10;
		digits++;
	}
	return (digits);
}

t_column_sizes 	get_column_sizes(const t_node* const node) {
	t_column_sizes columnSizes = {
			1,
			1,
			1,
			1
	};

	for (size_t i = 0; i < node->vector->size; i++) {
		const t_node *child_node = (const t_node *)node->vector->arr[i];
		columnSizes.nb_links = MAX(columnSizes.nb_links, get_amount_digits(child_node->statbuf.st_nlink));
		columnSizes.user = MAX(columnSizes.user, ft_strlen(get_username(&child_node->statbuf)));
		columnSizes.group = MAX(columnSizes.group, ft_strlen(get_groupname(&child_node->statbuf)));
		columnSizes.filesize = MAX(columnSizes.filesize, get_amount_digits(child_node->statbuf.st_size));
	}
	return (columnSizes);
}
