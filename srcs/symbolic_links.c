//
// Created by pde-bakk on 1/18/23.
//

#include <unistd.h>
#include <string.h>
#include "t_node.h"
#include "ft_ls.h"

char* get_symlink_path(const t_node* dataObj) {
	static char buf[PATH_MAX];
	ssize_t nbytes, buffer_size = dataObj->statbuf.st_size + 1;

	if (dataObj->statbuf.st_size == 0) {
		buffer_size = PATH_MAX;
	}
	nbytes = readlink(dataObj->fullpath, buf, buffer_size);
	if (nbytes == -1) {
		return (NULL);
	}
	buf[nbytes] = '\0';
	return (buf);
}
