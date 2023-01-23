//
// Created by pde-bakk on 1/16/23.
//

#include "t_node.h"
#include "flags.h"
#include "ft_printf.h"
#include "printing.h"
#include "ft_ls.h"
#include "libft.h"

static bool please_print_another_newline = false;

static void print_short(const t_node* dataObj) {
	if (ft_strchr(dataObj->name, ' ')) {
		ft_printf("'%s'", dataObj->name);
	} else {
		ft_printf("%s", dataObj->name);
	}
}

static void print_total_blocks(const t_ptrvector* vec) {
	size_t total = 0;
	size_t total2 = 0;
	for (size_t i = 0; i < vec->size; i++) {
		const t_node* item = vec->arr[i];
		total2 += item->statbuf.st_blocks / 2;
		total += item->statbuf.st_size / 1024;
		/*
		 * ls (and therefore ft_ls too) defines a block as 1024 bytes.
		 */
	}
	ft_printf("total %lu\n", MAX(total, total2));
}

static void print_object_short(const t_node* dataObj) {
	if (S_ISDIR(dataObj->statbuf.st_mode)) {
		for (size_t i = 0; i < dataObj->vector->size; i++) {
			print_short(dataObj->vector->arr[i]);
			if (i != dataObj->vector->size - 1)
				ft_printf("  ");
		}
	} else if (dataObj->name) {
		print_short(dataObj);
	}
	if (!S_ISDIR(dataObj->statbuf.st_mode) || dataObj->vector->size > 0)
		ft_printf("\n");
}

static void print_object_long(const t_node* dataObj) {
	if (S_ISDIR(dataObj->statbuf.st_mode)) {
		print_total_blocks(dataObj->vector);
		const t_column_sizes columnSizes = get_column_sizes(dataObj);
		for (size_t i = 0; i < dataObj->vector->size; i++) {
			print_long_listing_format(dataObj->vector->arr[i], &columnSizes);
		}
	} else {
		print_long_listing_format(dataObj, NULL);
	}
}

void print_object(const t_node* dataObj) {
	if (dataObj->vector->size > 1 && (!(g_flags & FLAG_f) || g_flags & FLAG_t)) {
		ptrvector_sort(dataObj->vector, &compare_nodes);
	}

	if (S_ISDIR(dataObj->statbuf.st_mode) && (g_flags & FLAG_R)) {
		if (please_print_another_newline)
			ft_printf("\n");
		ft_printf("%s:\n", dataObj->fullpath);
	}

	if (g_flags & FLAG_l) {
		print_object_long(dataObj);
	} else {
		print_object_short(dataObj);
	}
	if (g_flags & FLAG_R)
		please_print_another_newline = true;
}
