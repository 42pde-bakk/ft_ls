//
// Created by peer on 8-11-22.
//

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"
#include "flags.h"
#include <dirent.h>
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


int main(int argc, char** argv) {
	unsigned int	flags;
	t_ptrvector		*file_vector = ptrvector_init(4, false);
	t_data			*root_obj = create_new_object_root();

	if (!file_vector || !root_obj) {
		exit(EXIT_FAILURE);
	}
	(void)argc;

	flags = parse_flags(argv, file_vector);
	if (flags == -1u)
		exit(EXIT_FAILURE);

	if (file_vector->size == 0) {
		t_data*	dataObj = create_new_object_blank(".", true);
		for (size_t i = 0; i < dataObj->vector->size; i++) {
			ptrvector_pushback(root_obj->vector, dataObj->vector->arr[i]);
		}
		ptrvector_destroy(dataObj->vector);
		free(dataObj->name);
		free(dataObj);
//		ptrvector_pushback(root_obj->vector, dataObj);
	} else {
		for (size_t i = 0; i < file_vector->size; i++) {
			const char* const filename = file_vector->arr[i];
			unsigned char filetype = get_filetype(filename);
			if (filetype != DT_UNKNOWN) {
				t_data*	dataObj = create_new_object_of_type(filename, filetype, true);
				ptrvector_pushback(root_obj->vector, dataObj);
				dataObj->parent = root_obj;
			}
		}
	}
	// Then sort the entries and print them
	print_object(root_obj);

	ptrvector_destroy(file_vector);
	destroy_object(root_obj);
	return (EXIT_SUCCESS);
}
