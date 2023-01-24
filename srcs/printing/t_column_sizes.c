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

t_column_sizes get_column_sizes(const t_node* const node) {
	t_column_sizes columnSizes = {
			1,
			1,
			1,
			1
	};
	const char* username;
	const char* groupname;

	for (size_t i = 0; i < node->vector->size; i++) {
		const t_node* child_node = (const t_node*)node->vector->arr[i];
		username = get_username(&child_node->statbuf);
		groupname = get_groupname(&child_node->statbuf);
		columnSizes.nb_links = MAX(columnSizes.nb_links, get_amount_digits(child_node->statbuf.st_nlink));
		columnSizes.user = MAX(columnSizes.user, username ? ft_strlen(username) : 5);
		columnSizes.group = MAX(columnSizes.group, groupname ? ft_strlen(groupname) : 5);
		columnSizes.filesize = MAX(columnSizes.filesize, get_amount_digits(child_node->statbuf.st_size));
	}
	return (columnSizes);
}
