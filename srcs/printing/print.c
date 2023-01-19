//
// Created by pde-bakk on 1/16/23.
//

#include <pwd.h>
#include <grp.h>
#include "t_node.h"
#include "flags.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_ls.h"
t_column_sizes 	get_column_sizes(const t_node* node);
void	print_long_listing_format(const t_node* dataObj, const t_column_sizes* columnSizes);
static bool	please_print_another_newline = false;

static void print_short(const t_node* dataObj) {
	ft_printf("%s", dataObj->name);
}

static void print_total_blocks(const t_ptrvector* vec) {
	size_t total = 0;
	for (size_t i = 0; i < vec->size; i++) {
		const t_node* item = vec->arr[i];
		total += item->statbuf.st_blocks / 2;
		/*
		 * The / 2 is because stat sees a block as 512 bytes,
		 * but ls (and therefore ft_ls too) use 1024 bytes.
		 * I could also have used the filesize / 1024, but I'll stick to this for now.
		 */
	}
	ft_printf("total %lu\n", total);
}

void print_object(const t_node* dataObj) {
	if (dataObj->vector->size > 1 && (!(g_flags & FLAG_f) || g_flags & FLAG_t)) {
		ptrvector_sort(dataObj->vector, &compare_nodes);
	}

	if (g_flags & FLAG_l) {
		if (S_ISDIR(dataObj->statbuf.st_mode)) {
			if (g_flags & FLAG_R) {
				if (please_print_another_newline)
					ft_printf("\n");
				ft_printf("%s:\n", dataObj->fullpath);
			}
			print_total_blocks(dataObj->vector);
			const t_column_sizes columnSizes = get_column_sizes(dataObj);
			for (size_t i = 0; i < dataObj->vector->size; i++) {
				print_long_listing_format(dataObj->vector->arr[i], &columnSizes);
			}
			if (g_flags & FLAG_R) {
				please_print_another_newline = true;
//				ft_printf("\n");
			}
		} else {
			print_long_listing_format(dataObj, NULL);
		}
	} else {
		if (S_ISDIR(dataObj->statbuf.st_mode)) {
			if (g_flags & FLAG_R) {
				ft_printf("%s:\n", dataObj->fullpath);
			}
			if (dataObj->vector->size > 0) {
				for (size_t i = 0; i < dataObj->vector->size; i++) {
					print_short(dataObj->vector->arr[i]);
					if (i != dataObj->vector->size - 1)
						ft_printf("  ");
				}
				ft_printf("%c", '\n');
			}
		} else if (dataObj->name) {
			print_short(dataObj);
			ft_printf("\n");
		}
	}
}
