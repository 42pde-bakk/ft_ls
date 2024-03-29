//
// Created by pde-bakk on 1/18/23.
//

#include "vector.h"
#include "ft_printf.h"
#include "flags.h"

unsigned int g_flags;
static char* g_program_name = "ft_ls";

const char* get_program_name() {
	return (g_program_name);
}

unsigned int parse_flags(char** argv, t_ptrvector* file_vector) {
	unsigned int flags = 0;

	g_program_name = argv[0];
	for (size_t i = 1; argv[i]; i++) {
		if (argv[i][0] == '-') {
			for (size_t n = 1; argv[i][n]; n++) {
				const char flag = argv[i][n];
				switch (flag) {
					case 'l':
						flags |= FLAG_l;
						break;
					case 'R':
						flags |= FLAG_R;
						break;
					case 'a':
						flags |= FLAG_a;
						break;
					case 'r':
						flags |= FLAG_r;
						break;
					case 't':
						flags |= FLAG_t;
						break;
					case 'f':
						flags |= FLAG_f;
						flags &= ~FLAG_t;
						break;
					case 'c':
						flags |= FLAG_c;
						break;
					default:
						ft_printf("%s: invalid option -- '%c'\n", get_program_name(), flag);
						exit(EXIT_FAILURE);
				}
			}
		} else {
			// Add the file/folder to our vector
			ptrvector_pushback(file_vector, argv[i]);
		}
	}
	g_flags = flags;
	return (flags);
}
