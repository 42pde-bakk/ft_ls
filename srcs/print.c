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

static bool	please_print_another_newline = false;

static int get_amount_digits(size_t n) {
	int digits = 1;
	while (n > 9) {
		n /= 10;
		digits++;
	}
	return (digits);
}

static void print_permissions(const struct stat* statbuf) {
	const __mode_t mode = statbuf->st_mode;
	const char perms[] = {
			S_ISSOCK(mode) ? 's' : S_ISLNK(mode) ? 'l' : S_ISDIR(mode) ? 'd' : S_ISFIFO(mode) ? 'p' : '-',
			mode & S_IRUSR ? 'r' : '-',
			mode & S_IWUSR ? 'w' : '-',
			mode & S_ISUID ? 'S' : (mode & S_IXUSR) ? 'x' : '-',

			mode & S_IRGRP ? 'r' : '-',
			mode & S_IWGRP ? 'w' : '-',
			mode & S_ISGID ? 'S' : (mode & S_IXGRP) ? 'x' : '-',

			mode & S_IROTH ? 'r' : '-',
			mode & S_IWOTH ? 'w' : '-',
			mode & S_ISVTX ? 'T' : (mode & S_IXOTH) ? 'x' : '-',
			'\0'
	};
	ft_printf("%s", perms);
}

static const char* get_username(const struct stat* statbuf) {
	struct passwd* passwd_data = getpwuid(statbuf->st_uid);
	return (passwd_data->pw_name);
}

static const char* get_groupname(const struct stat* statbuf) {
	struct group* group_data = getgrgid(statbuf->st_gid);
	return (group_data->gr_name);
}

static void print_mtime(const struct stat* statbuf) {
	char* p = ctime(&statbuf->st_mtim.tv_sec);
	if (!p)
		return;
	p[ft_strlen(p) - 9] = 0;
	ft_printf(" %s", p + 4);
}

static void print_name(const t_node* dataObj) {
	char* symlink_path;

	if (S_ISLNK(dataObj->statbuf.st_mode) && (symlink_path = get_symlink_path(dataObj)) != NULL) {
		ft_printf(" %s -> %s\n", dataObj->name, symlink_path);
		free(symlink_path);
	} else {
		ft_printf(" %s\n", dataObj->name);
	}
}

static void print_long(const t_node* dataObj) {
	print_permissions(&dataObj->statbuf);
	ft_printf(" %lu", dataObj->statbuf.st_nlink);
	ft_printf(" %s", get_username(&dataObj->statbuf));
	ft_printf(" %s", get_groupname(&dataObj->statbuf));
	ft_printf(" %ld", dataObj->statbuf.st_size);
	print_mtime(&dataObj->statbuf);
	print_name(dataObj);
}

static void print_long_with_columnsizes(const t_node* dataObj, const t_column_sizes* columnSizes) {
	print_permissions(&dataObj->statbuf);
	ft_printf(" %*d", columnSizes->nb_links, dataObj->statbuf.st_nlink);
	ft_printf(" %-*s", columnSizes->user, get_username(&dataObj->statbuf));
	ft_printf(" %-*s", columnSizes->group, get_groupname(&dataObj->statbuf));
	ft_printf(" %*d", columnSizes->filesize, dataObj->statbuf.st_size);
	print_mtime(&dataObj->statbuf);
	print_name(dataObj);
}

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

static t_column_sizes 	get_column_sizes(const t_node* const node) {
	t_column_sizes columnSizes = {
			1,
			1,
			1,
			1
	};

	for (size_t i = 0; i < node->vector->size; i++) {
		const t_node *child_node = (const t_node *)node->vector->arr[i];
		columnSizes.nb_links = MAX(columnSizes.nb_links, get_amount_digits(child_node->statbuf.st_nlink));
		columnSizes.user = MAX(columnSizes.user, ft_strlen(get_username(&child_node->statbuf)));
		columnSizes.group = MAX(columnSizes.group, ft_strlen(get_groupname(&child_node->statbuf)));
		columnSizes.filesize = MAX(columnSizes.filesize, get_amount_digits(child_node->statbuf.st_size));
	}
	return (columnSizes);
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
				print_long_with_columnsizes(dataObj->vector->arr[i], &columnSizes);
			}
			if (g_flags & FLAG_R) {
				please_print_another_newline = true;
//				ft_printf("\n");
			}
		} else {
			print_long(dataObj);
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
