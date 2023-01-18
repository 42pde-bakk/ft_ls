//
// Created by peer on 13-11-22.
//
#include <string.h>
#include "flags.h"
#include "t_node.h"
#include "libft.h"
#include "ft_ls.h"

static int ft_strcmp(const char* const lhs, const char* const rhs) {
	size_t i = 0;

	while (lhs[i] && rhs[i] && lhs[i] == rhs[i]) {
		i++;
	}
	return (lhs[i] - rhs[i]);
}

static int	case_insensitive_strcmp(const char* lhs, const char* rhs) {
	size_t i = 0;

	if (lhs[0] == '.')
		++lhs;
	if (rhs[0] == '.')
		++rhs;
	while (lhs[i] && rhs[i] && ft_tolower(lhs[i]) == ft_tolower(rhs[i])) {
		i++;
	}
	return (ft_tolower(lhs[i]) - ft_tolower(rhs[i]));
}

static void	swap(t_node *dataObjects[], const idx_t i, const idx_t j) {
	t_node	*tmp = dataObjects[i];

	dataObjects[i] = dataObjects[j];
	dataObjects[j] = tmp;
}

int		compare_by_time(struct timespec lhs, struct timespec rhs) {
	if (lhs.tv_sec == rhs.tv_sec)
		return ((int)(lhs.tv_nsec - rhs.tv_nsec));
	else
		return ((int)(lhs.tv_sec - rhs.tv_sec));
}

static bool	shouldSwap(const t_node *dataObject, const t_node *pivot) {
	int cmp_ret;

	if (g_flags & FLAG_t) {
		cmp_ret = compare_by_time(pivot->statbuf.st_mtim, dataObject->statbuf.st_mtim);
	} else {
		cmp_ret = case_insensitive_strcmp(dataObject->name, pivot->name);
		if (cmp_ret == 0) {
			cmp_ret = ft_strcmp(pivot->name, dataObject->name);
		}
	}

	if (g_flags & FLAG_r) {
		cmp_ret *= -1;
	}
	return (cmp_ret < 0);
}

static idx_t	partition(t_node **dataObjects, const idx_t low, const idx_t high) {
	t_node *pivot = dataObjects[high];
	idx_t i = low - 1; // Index of smaller element and indicates the right position of pivot found so far

	for (idx_t j = low; j <= high - 1; j++) {
		// if current element is smaller than the pivot
		if (shouldSwap(dataObjects[j], pivot)) {
			++i;
			swap(dataObjects, i, j);
		}
	}
	swap(dataObjects, i + 1, high);
	return (i + 1);
}

void	quickSort(t_node **dataObjects, idx_t low, idx_t high) {
	if (low < high) {
		idx_t partitionIndex = partition(dataObjects, low, high);

		quickSort(dataObjects, low, partitionIndex - 1);
		quickSort(dataObjects, partitionIndex + 1, high);
	}
}
//
//void	sort_dataObjects(t_node **dataObjects, const size_t dataObject_amount) {
//	quickSort(dataObjects, 0, (idx_t)(dataObject_amount - 1));
//}
