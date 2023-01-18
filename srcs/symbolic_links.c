//
// Created by pde-bakk on 1/18/23.
//

#include <unistd.h>
#include <stdio.h>
#include "t_node.h"

char*	get_symlink_path(const t_node* dataObj) {
	char* buf;
	ssize_t nbytes, buffer_size = dataObj->statbuf.st_size + 1;

	if (dataObj->statbuf.st_size == 0) {
		buffer_size = PATH_MAX;
	}
	buf = malloc(buffer_size);
	if (buf == NULL)
		exit(EXIT_FAILURE);
	nbytes = readlink(dataObj->fullpath, buf, buffer_size);
	if (nbytes == -1) {
		perror("readlink");
		exit(EXIT_FAILURE);
	}
	buf[nbytes] = '\0';
	return (buf);
}