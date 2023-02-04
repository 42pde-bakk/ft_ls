//
// Created by peer on 03-02-23.
//
#include <stdio.h>
#include "ft_ls.h"

int compare_rootnodes(const void* v_dataObject, const void* v_pivot) {
	const t_node* dataObject = (t_node*)v_dataObject;
	const t_node* pivot = (t_node*)v_pivot;

	fprintf(stderr, "lhs= %s -> %u, rhs = %s -> %u\n", dataObject->name, dataObject->statbuf.st_mode, pivot->name, pivot->statbuf.st_mode);
//	if (dataObject->statbuf.st_mode != pivot->statbuf.st_mode) {
	return (dataObject->statbuf.st_mode > pivot->statbuf.st_mode);
//	}
//	return (compare_nodes(v_dataObject, v_pivot));
}
