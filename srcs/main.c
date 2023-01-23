//
// Created by peer on 8-11-22.
//

#include <stddef.h>
#include "libft.h"
#include "flags.h"
#include "t_node.h"
#include "ft_ls.h"

static bool is_dot_or_double_dot(const char* str) {
	return (ft_strncmp(str, ".", 2) == 0 || ft_strncmp(str, "..", 3) == 0);
}

void start_ls(t_node* dataObject) {
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

int main(int argc, char** argv) {
	unsigned int flags;
	t_ptrvector* file_vector = ptrvector_init(4, false);
	t_node* rootObj;

	if (!file_vector) {
		exit(EXIT_FAILURE);
	}
	(void)argc;

	flags = parse_flags(argv, file_vector);
	if (flags == -1u)
		exit(EXIT_FAILURE);

	if (file_vector->size == 0) {
		rootObj = create_new_rootnode(".");
		start_ls(rootObj);
		destroy_object(rootObj);
	} else {
		for (size_t i = 0; i < file_vector->size; i++) {
			const char* const filename = file_vector->arr[i];
			rootObj = create_new_rootnode(filename);
			start_ls(rootObj);
			destroy_object(rootObj);
		}
	}
	ptrvector_destroy(file_vector);
	return (EXIT_SUCCESS);
}
