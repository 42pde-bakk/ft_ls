//
// Created by peer on 03-02-23.
//
#include "ft_ls.h"

int compare_rootnodes(const void* v_dataObject, const void* v_pivot) {
	const t_node* dataObject = (t_node*)v_dataObject;
	const t_node* pivot = (t_node*)v_pivot;

	if (dataObject->statbuf.st_mode != pivot->statbuf.st_mode) {
		return (dataObject->statbuf.st_mode > pivot->statbuf.st_mode);
	}
	return (compare_nodes(v_dataObject, v_pivot));
}
