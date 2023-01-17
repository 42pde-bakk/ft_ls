//
// Created by peer on 8-11-22.
//

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"
#include "flags.h"
#include "data_obj.h"
unsigned int g_flags;

unsigned int parse_flags(char** argv, t_ptrvector* file_vector) {
	unsigned int flags = 0;

	for (size_t i = 1; argv[i]; i++) {
		if (argv[i][0] == '-') {
			for (size_t n = 1; argv[i][n]; n++) {
				const char flag = argv[i][n];
				switch (flag) {
					case 'l':
						flags |= FLAG_l;
						break ;
					case 'R':
						flags |= FLAG_R;
						break ;
					case 'a':
						flags |= FLAG_a;
						break ;
					case 'r':
						flags |= FLAG_r;
						break ;
					case 't':
						flags |= FLAG_t;
						break ;
					case 'f':
						flags |= FLAG_f;
						break ;
					default:
						ft_printf("ls: invalid option -- '%c'\n", flag);
						exit(EXIT_FAILURE);
				}
			}
		}
		else {
			// Add the file/folder to our vector
			ptrvector_pushback(file_vector, argv[i]);
		}
	}
	g_flags = flags;
	return (flags);
}

bool	is_dot_or_double_dot(const char* str) {
	return (ft_strncmp(str, ".", 2) == 0 || ft_strncmp(str, "..", 3) == 0);
}

void	run_dmc(t_data* dataObject) {
	if (S_ISDIR(dataObject->statbuf.st_mode)) {
		collect_children_nodes(dataObject);
	}
	print_object(dataObject);
	if (S_ISDIR(dataObject->statbuf.st_mode) && (g_flags & FLAG_R) && !(g_flags & FLAG_d)) {
		for (size_t i = 0; i < dataObject->vector->size; i++) {
			t_data* child = dataObject->vector->arr[i];
			(void)child;

			if (!is_dot_or_double_dot(child->name) && S_ISDIR(child->statbuf.st_mode))
				run_dmc(child);
		}
	}
}

int main(int argc, char** argv) {
	unsigned int	flags;
	t_ptrvector		*file_vector = ptrvector_init(4, false);
	t_data* rootObj;

	if (!file_vector) {
		exit(EXIT_FAILURE);
	}
	(void)argc;

	flags = parse_flags(argv, file_vector);
	if (flags == -1u)
		exit(EXIT_FAILURE);

	if (file_vector->size == 0) {
		rootObj = create_new_rootnode(".");
		run_dmc(rootObj);
		destroy_object(rootObj);
	} else {
		for (size_t i = 0; i < file_vector->size; i++) {
			const char* const filename = file_vector->arr[i];
			rootObj = create_new_rootnode(filename);
			run_dmc(rootObj);
			destroy_object(rootObj);
		}
	}
	ptrvector_destroy(file_vector);
	return (EXIT_SUCCESS);
}
