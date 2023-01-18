//
// Created by peer on 12-11-22.
//

#include <stdio.h>
#include "flags.h"
#include "t_node.h"

void	collect_children_nodes(t_node *ls_obj) {
	DIR*	dir;
	struct dirent *pDirent;
	t_node*	childNode;

	dir = opendir(ls_obj->fullpath);
	if (dir == NULL) {
		return ;
	}
	while ((pDirent = readdir(dir)) != NULL) {
		if (!(g_flags & FLAG_a)) {
			if (pDirent->d_name[0] == '.' && !(g_flags & FLAG_f))
				continue ;
		}
		childNode = create_new_object(ls_obj->fullpath, pDirent->d_name);
		if (!childNode)
			continue;

		ptrvector_pushback(ls_obj->vector, childNode);
	}
	closedir(dir);
}
