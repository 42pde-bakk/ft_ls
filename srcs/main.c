//
// Created by peer on 8-11-22.
//

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"
#include "flags.h"
#include <dirent.h>
#include <stdio.h>
#include "libft.h"
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

//void switchcase(const char *const prefix, const char *const name, bool recurse);
//
//
//
//void switchcase(const char *const prefix, const char *const name, bool recurse) {
//	struct stat statbuf;
//	char*	fullpath;
//
//	fullpath = ft_str3join(prefix, "/", name);
//	if (fullpath == NULL)
//		exit(EXIT_FAILURE);
//	ft_memset(&statbuf, 0, sizeof(statbuf));
////	printf("name = %s, fullpath = %s\n", name, fullpath);
//	if (stat(fullpath, &statbuf) == -1) {
//		perror("stat");
//		exit(EXIT_FAILURE);
//	}
//
//	switch (statbuf.st_mode & S_IFMT) {
//		case S_IFBLK:
//			ft_printf("block device\n");
//			break;
//		case S_IFCHR:
//			ft_printf("character device\n");
//			break;
//		case S_IFDIR:
////			ft_printf("directory, recurse = %d, Recruse_flag=%d\n", recurse, g_flags & FLAG_R);
//			if (recurse)
//				ls_directory(NULL);
//			else
//				ls_file(name);
//			break;
//		case S_IFIFO:
//			ft_printf("FIFO/pipe\n");
//			break;
//		case S_IFLNK:
//			ft_printf("symlink\n");
//			break;
//		case S_IFREG:
////			ft_printf("regular file\n");
//			ls_file(name);
//			break;
//		case S_IFSOCK:
//			ft_printf("socket\n");
//			break;
//		default:
//			ft_printf("unknown?\n");
//			break;
//	}
//}

int main(int argc, char** argv) {
	unsigned int	flags;
	t_ptrvector		*file_vector = ptrvector_init(4, false);
//	t_ptrvector		*dataObj_vec = ptrvector_init(128, false);
	t_data			*root_obj = create_new_object_root();
	(void)argc;
	if (!file_vector || !root_obj) {
		exit(EXIT_FAILURE);
	}

	flags = parse_flags(argv, file_vector);
	if (flags == -1u)
		exit(EXIT_FAILURE);

	if (file_vector->size == 0) {
		t_data*	dataObj = create_new_object_blank(".", true);
		ptrvector_pushback(root_obj->vector, dataObj);
	} else {
		for (size_t i = 0; i < file_vector->size; i++) {
			const char* const filename = file_vector->arr[i];
			unsigned char filetype = get_filetype(filename);
			if (filetype != DT_UNKNOWN) {
				t_data*	dataObj = create_new_object_of_type(".", filename, filetype, true);
				ptrvector_pushback(root_obj->vector, dataObj);
				dataObj->parent = root_obj;
			}
		}
	}

	// Then sort the entries
	print_object(root_obj);

	// and output them
//	for (size_t i = 0; i < root_obj->vector->size; i++) {
//		print_object(root_obj->vector->arr[i]);
//		root_obj->vector->arr[i] = destroy_object(root_obj->vector->arr[i]);
////		ft_printf("\n");
//	}
	ptrvector_destroy(file_vector);
	destroy_object(root_obj);
	return (EXIT_SUCCESS);
}
