//
// Created by peer on 19-1-23.
//

#include "sorting.h"
#include "flags.h"

static int compare_by_time(const struct timespec* lhs, const struct timespec* rhs) {
	if (lhs->tv_sec != rhs->tv_sec)
		return (int)(lhs->tv_sec - rhs->tv_sec);
	return (int)(lhs->tv_nsec - rhs->tv_nsec);
}

static int cmp_ctime(const t_node* a, const t_node* b, t_func_cmpstrings cmp) {
	const int diff = compare_by_time(&a->statbuf.st_ctim, &b->statbuf.st_ctim);
	if (diff == 0) {
		return (cmp(b->name, a->name));
	}
	return (diff);
}

/*
 * https://github.com/coreutils/coreutils/blob/master/src/ls.c#L3848
 */
static int cmp_mtime(const t_node* a, const t_node* b, t_func_cmpstrings cmp) {
	const int diff = compare_by_time(&a->statbuf.st_mtim, &b->statbuf.st_mtim);
//	dprintf(2, "a=%s, [%ld %ld], b=%s [%ld %ld], diff=%d\n", a->name, a->statbuf.st_mtim.tv_sec, a->statbuf.st_mtim.tv_nsec, b->name, b->statbuf.st_mtim.tv_sec, b->statbuf.st_mtim.tv_nsec, diff);

	if (diff == 0) {
//		dprintf(2, "diff was 0, returning cmp: %d\n", cmp(a->name, b->name));
		return (cmp(b->name, a->name));
	}
	return (diff);
}

int sort_on_timestamp(const t_node* dataObject, const t_node* pivot, t_func_cmpstrings strcmpFunc) {
	if (g_flags & FLAG_c) {
		return (cmp_ctime(pivot, dataObject, strcmpFunc));
	}
	return (cmp_mtime(pivot, dataObject, strcmpFunc));
}
