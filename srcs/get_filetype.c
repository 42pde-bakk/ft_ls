//
// Created by peer on 12-11-22.
//
#include <sys/stat.h>
#include "libft.h"
#include "dirent.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>

unsigned char get_filetype(const char* name) {
	struct stat statbuf;

	ft_memset(&statbuf, 0, sizeof(statbuf));
	if (stat(name, &statbuf) == -1) {
		ft_dprintf(STDERR_FILENO, "ls: cannot access '%s': %s\n", name, strerror(errno));
		return (DT_UNKNOWN);
	}

	switch (statbuf.st_mode & S_IFMT) {
		case S_IFBLK: return (DT_BLK);
		case S_IFCHR: return (DT_CHR);
		case S_IFDIR: return (DT_DIR);
		case S_IFIFO: return (DT_FIFO);
		case S_IFLNK: return (DT_LNK);
		case S_IFREG: return (DT_REG);
		case S_IFSOCK: return (DT_SOCK);
		default: return (DT_UNKNOWN);
	}
}
