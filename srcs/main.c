//
// Created by peer on 8-11-22.
//

#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "flags.h"
#include "t_node.h"
#include "ft_ls.h"
#include "ft_printf.h"
#include <stdio.h>

int is_tty;

static bool is_dot_or_double_dot(const char* const str) {
	return (ft_strncmp(str, ".", 2) == 0 || ft_strncmp(str, "..", 3) == 0);
}

static void start_ls(t_node* dataObject) {
	if (S_ISDIR(dataObject->statbuf.st_mode)) {
		if (collect_children_nodes(dataObject) == EXIT_FAILURE) {
			return;
		}
	}
	print_object(dataObject);
	if (S_ISDIR(dataObject->statbuf.st_mode) && (g_flags & FLAG_R) && !(g_flags & FLAG_d)) {
		for (size_t i = 0; i < dataObject->vector->size; i++) {
			t_node* child = dataObject->vector->arr[i];

			if (!is_dot_or_double_dot(child->name) && S_ISDIR(child->statbuf.st_mode))
				start_ls(child);
		}
	}
}

void	loop_objects(const t_ptrvector* objects) {
	for (size_t i = 0; i < objects->size; i++) {
		t_node* rootObj = objects->arr[i];
		if (objects->size > 1 && S_ISDIR(rootObj->statbuf.st_mode) && !(g_flags & FLAG_R)) {
			ft_printf("%s:\n", rootObj->name);
		}
		start_ls(rootObj);
		if (objects->size > 1 && S_ISDIR(rootObj->statbuf.st_mode) && !(g_flags & FLAG_R) && i < objects->size - 1) {
			// Always print a newline at the end except for the last one
			ft_printf("\n");
		}
		destroy_object(rootObj);
	}
}

int main(int argc, char** argv) {
	unsigned int flags;
	t_ptrvector* file_vector = ptrvector_init(4, false);
	t_node* rootObj;

	if (!file_vector) {
		exit(EXIT_FAILURE);
	}
	is_tty = isatty(STDOUT_FILENO);

	flags = parse_flags(argv, file_vector);
	if (flags == -1u)
		exit(EXIT_FAILURE);

	if (file_vector->size == 0) {
		rootObj = create_new_rootnode(".");
		if (rootObj) {
			start_ls(rootObj);
			destroy_object(rootObj);
		}
	}
	else {
		t_ptrvector*	directories = ptrvector_init(4, false);
		t_ptrvector*	regular_files = ptrvector_init(4, false);
		if (directories == NULL || regular_files == NULL)
			exit(EXIT_FAILURE);
		for (size_t i = 0; i < file_vector->size; i++) {
			rootObj = create_new_rootnode(file_vector->arr[i]);
			if (rootObj == NULL)
				continue;
			ptrvector_pushback(S_ISDIR(rootObj->statbuf.st_mode) ? directories : regular_files, rootObj);
		}
		// Sort files based on their names/timestamp
		ptrvector_sort(directories, &compare_nodes);
		ptrvector_sort(regular_files, &compare_nodes);

		loop_objects(regular_files);
		if (regular_files->size > 0 && directories->size > 0) {
			ft_printf("\n");
		}
		loop_objects(directories);
		ptrvector_destroy(regular_files);
		ptrvector_destroy(directories);
	}
	ptrvector_destroy(file_vector);
	return (EXIT_SUCCESS);
	(void)argc;
}
