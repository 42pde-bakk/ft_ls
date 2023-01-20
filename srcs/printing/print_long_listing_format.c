//
// Created by peer on 19-1-23.
//

#include <grp.h>
#include <pwd.h>
#include "t_node.h"
#include "ft_ls.h"
#include "ft_printf.h"
#include "libft.h"
#include "flags.h"
#include "printing.h"

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

const char* get_username(const struct stat* statbuf) {
	struct passwd* passwd_data = getpwuid(statbuf->st_uid);
	return (passwd_data->pw_name);
}

const char* get_groupname(const struct stat* statbuf) {
	struct group* group_data = getgrgid(statbuf->st_gid);
	return (group_data->gr_name);
}

static void print_time(const struct stat* statbuf) {
	char* p;

	if (g_flags & FLAG_c) {
		p = ctime(&statbuf->st_ctim.tv_sec);
	} else {
		p = ctime(&statbuf->st_mtim.tv_sec);
	}
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
	print_time(&dataObj->statbuf);
	print_name(dataObj);
}

static void print_long_with_columnsizes(const t_node* dataObj, const t_column_sizes* columnSizes) {
	print_permissions(&dataObj->statbuf);
	ft_printf(" %*d", columnSizes->nb_links, dataObj->statbuf.st_nlink);
	ft_printf(" %-*s", columnSizes->user, get_username(&dataObj->statbuf));
	ft_printf(" %-*s", columnSizes->group, get_groupname(&dataObj->statbuf));
	ft_printf(" %*d", columnSizes->filesize, dataObj->statbuf.st_size);
	print_time(&dataObj->statbuf);
	print_name(dataObj);
}

void	print_long_listing_format(const t_node* dataObj, const t_column_sizes* columnSizes) {
	if (columnSizes == NULL)
		return (print_long(dataObj));
	print_long_with_columnsizes(dataObj, columnSizes);
}