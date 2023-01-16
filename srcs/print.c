//
// Created by pde-bakk on 1/16/23.
//

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include "data_obj.h"
#include "flags.h"
#include "libft.h"
#include "ft_printf.h"

void	print_permissions(const struct stat* statbuf) {
	const char	perms[] = {
			S_ISDIR(statbuf->st_mode) ? 'd' : '-',
			statbuf->st_mode & S_IRUSR ? 'r' : '-',
			statbuf->st_mode & S_IWUSR ? 'w' : '-',
			statbuf->st_mode & S_IXUSR ? 'x' : '-',

			statbuf->st_mode & S_IRGRP ? 'r' : '-',
			statbuf->st_mode & S_IWGRP ? 'w' : '-',
			statbuf->st_mode & S_IXGRP ? 'x' : '-',

			statbuf->st_mode & S_IROTH ? 'r' : '-',
			statbuf->st_mode & S_IWOTH ? 'w' : '-',
			statbuf->st_mode & S_IXOTH ? 'x' : '-',
			'\0'
	};
	ft_printf("%s", perms);
}

const char*	get_username(const struct stat* statbuf) {
	struct passwd* passwd_data = getpwuid(statbuf->st_uid);
	return (passwd_data->pw_name);
}

const char*	get_groupname(const struct stat* statbuf) {
	struct group* group_data = getgrgid(statbuf->st_gid);
	return (group_data->gr_name);
}

void	convert_string_to_lower(char* s) {
	for (size_t i = 0; s[i]; i++) {
		s[i] = (char)ft_tolower(s[i]);
	}
}

void	print_mtime(const struct stat* statbuf) {
	char* p = ctime(&statbuf->st_mtim.tv_sec);
	if (!p)
		return ;
	p[ft_strlen(p) - 9] = 0;
	convert_string_to_lower(p);
	ft_printf(" %s", p + 4);
}

void	print_long(const t_data* dataObj) {
	print_permissions(&dataObj->statbuf);
	ft_printf(" %lu", dataObj->statbuf.st_nlink);
	ft_printf(" %s", get_username(&dataObj->statbuf));
	ft_printf(" %s", get_groupname(&dataObj->statbuf));
	ft_printf(" %ld", dataObj->statbuf.st_size);
	print_mtime(&dataObj->statbuf);
	ft_printf(" %s\n", dataObj->name);
}

void	print_short(const t_data* dataObj) {
	ft_printf("%s", dataObj->name);
}

void	print_total_blocks(const t_ptrvector* vec) {
	size_t total = 0;
	for (size_t i = 0; i < vec->size; i++) {
		const t_data* item = vec->arr[i];
		total += item->statbuf.st_blocks / 2;
		/*
		 * The / 2 is because stat sees a block as 512 bytes,
		 * but ls (and therefore ft_ls too) use 1024 bytes.
		 * I could also have used the filesize / 1024, but I'll stick to this for now.
		 */
	}
	ft_printf("total %lu\n", total);
}

// returns if it printed the header
bool print_object(const t_data* dataObj) {
	bool print_header = false;

	if (dataObj->vector->size > 1) {
		sort_dataObjects((t_data **)dataObj->vector->arr, dataObj->vector->size);
	}


	if (g_flags & FLAG_l) {
		if (g_flags & FLAG_R) {
			ft_printf("%s:\n", dataObj->fullpath);
		}
		if (dataObj->vector->size > 1)
			print_total_blocks(dataObj->vector);
		for (size_t i = 0; i < dataObj->vector->size; i++) {
			print_long(dataObj->vector->arr[i]);
		}
	}
	else {
		if (dataObj->vector->size) {
			if (g_flags & FLAG_R) {
				ft_printf("%s:\n", dataObj->fullpath);
			}
			for (size_t i = 0; i < dataObj->vector->size; i++) {
				print_short(dataObj->vector->arr[i]);
				if (i != dataObj->vector->size - 1)
					ft_printf("  ");
			}
			ft_printf("%c", '\n');
		}
		else if (dataObj->name) {
			print_short(dataObj);
			ft_printf("\n");
		}
	}
	if (g_flags & FLAG_R) {
		ft_printf("\n");
	}
	return (print_header);
}