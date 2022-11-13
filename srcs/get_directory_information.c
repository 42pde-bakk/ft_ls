//
// Created by peer on 12-11-22.
//

#include <stdio.h>
#include "flags.h"
#include "data_obj.h"
#include "libft.h"

void collect_children_nodes(t_data *ls_obj) {
	DIR*	dir;
	struct dirent *pDirent;

	dir = opendir(ls_obj->fullpath);
	if (dir == NULL) {
		return ;
	}
	while ((pDirent = readdir(dir)) != NULL) {
		if (!(g_flags & FLAG_a)) {
			if (pDirent->d_name[0] == '.')
				continue ;
		}
		t_data*	childNode = create_new_object(ls_obj->fullpath, pDirent);

		if (g_flags & FLAG_R && childNode->type == DT_DIR)
			collect_children_nodes(childNode);

		childNode->parent = ls_obj;
		ptrvector_pushback(ls_obj->vector, childNode);
	}
	closedir(dir);
}
