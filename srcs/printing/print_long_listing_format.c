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
			mode & S_ISUID ? ((mode & S_IXUSR) ? 's' : 'S') : (mode & S_IXUSR) ? 'x' : '-',

			mode & S_IRGRP ? 'r' : '-',
			mode & S_IWGRP ? 'w' : '-',
			mode & S_ISGID ? ((mode & S_IXGRP) ? 's' : 'S') : (mode & S_IXGRP) ? 'x' : '-',

			mode & S_IROTH ? 'r' : '-',
			mode & S_IWOTH ? 'w' : '-',
			mode & S_ISVTX ? ((mode & S_IXOTH) ? 't' : 'T') : (mode & S_IXOTH) ? 'x' : '-',
			'\0'
	};
	ft_printf("%s", perms);
}

const char* get_username(const struct stat* statbuf) {
	const struct passwd* passwd_data = getpwuid(statbuf->st_uid);
	if (!passwd_data) {
		return (NULL);
	}
	return (passwd_data->pw_name);
}

const char* get_groupname(const struct stat* statbuf) {
	const struct group* group_data = getgrgid(statbuf->st_gid);
	if (!group_data) {
		return (NULL);
	}
	return (group_data->gr_name);
}

static void print_time(const struct stat* statbuf) {
	const time_t current_time = time(NULL);
	const time_t check_time = (g_flags & FLAG_c) ? statbuf->st_ctim.tv_sec : statbuf->st_mtim.tv_sec;
	char* p;
	size_t plen;

	p = ctime(&check_time);
	if (!p)
		return;
	plen = ft_strlen(p);
	if (check_time < current_time && (current_time - check_time) > (SECONDS_PER_YEAR / 2)) {
		p[10] = 0;
		p[plen - 1] = 0;
		ft_printf(" %s %s", p + 4, p + 19);
	} else {
		p[plen - 9] = 0;
		ft_printf(" %s", p + 4);
	}
}

static void print_name(const t_node* dataObj) {
	char* symlink_path;

	if (S_ISLNK(dataObj->statbuf.st_mode) && (symlink_path = get_symlink_path(dataObj)) != NULL) {
		ft_printf(" %s -> %s\n", dataObj->name, symlink_path);
	} else {
		if (is_tty && ft_strchr(dataObj->name, ' ') && (S_ISDIR(dataObj->statbuf.st_mode) || S_ISREG(dataObj->statbuf.st_mode)))
			ft_printf(" '%s'\n", dataObj->name);
		else
			ft_printf(" %s\n", dataObj->name);
	}
}

static void print_long(const t_node* dataObj) {
	const char* const username = get_username(&dataObj->statbuf);
	const char* const groupname = get_groupname(&dataObj->statbuf);

	print_permissions(&dataObj->statbuf);
	ft_printf(" %lu", dataObj->statbuf.st_nlink);
	if (!username) {
		ft_printf(" %u", dataObj->statbuf.st_uid);
	} else {
		ft_printf(" %s", username);
	}
	if (!groupname) {
		ft_printf(" %u", dataObj->statbuf.st_gid);
	} else {
		ft_printf(" %s", groupname);
	}
	ft_printf(" %lu", (unsigned long int)dataObj->statbuf.st_size);
	print_time(&dataObj->statbuf);
	print_name(dataObj);
}

static void print_long_with_columnsizes(const t_node* dataObj, const t_column_sizes* columnSizes) {
	const char* const username = get_username(&dataObj->statbuf);
	const char* const groupname = get_groupname(&dataObj->statbuf);

	print_permissions(&dataObj->statbuf);
	ft_printf(" %*d", columnSizes->nb_links, dataObj->statbuf.st_nlink);
	username ? ft_printf(" %-*s", columnSizes->user, username) : ft_printf(" %*u", columnSizes->user, dataObj->statbuf.st_uid);
	groupname ? ft_printf(" %-*s", columnSizes->group, groupname) : ft_printf(" %*u", columnSizes->group, dataObj->statbuf.st_gid);
	ft_printf(" %*lu", columnSizes->filesize, (unsigned long int)dataObj->statbuf.st_size);
	print_time(&dataObj->statbuf);
	print_name(dataObj);
}

void print_long_listing_format(const t_node* dataObj, const t_column_sizes* columnSizes) {
	if (columnSizes == NULL)
		return (print_long(dataObj));
	print_long_with_columnsizes(dataObj, columnSizes);
}
