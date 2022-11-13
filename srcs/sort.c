//
// Created by peer on 13-11-22.
//
#include <string.h>
#include "flags.h"
#include "data_obj.h"
#include "libft.h"
#include "ft_printf.h"
typedef int idx_t;

static int	case_insensitive_strcmp(const char* lhs, const char* rhs) {
	size_t i = 0;

	while (lhs[i] && rhs[i]) {
		if (ft_tolower(lhs[i]) != ft_tolower(rhs[i])) {
			break ;
		}
		i++;
	}
	return (ft_tolower(lhs[i]) - ft_tolower(rhs[i]));
}

static void	swap(t_data *dataObjects[], const idx_t i, const idx_t j) {
	t_data	*tmp = dataObjects[i];

	dataObjects[i] = dataObjects[j];
	dataObjects[j] = tmp;
}

static bool	shouldSwap(const t_data *dataObject, const t_data *pivot) {
	const int cmp_ret = case_insensitive_strcmp(dataObject->name, pivot->name);
//	ft_dprintf(2, "compare(%s?, %s) => %d\n", dataObject->name, pivot->name, cmp_ret);

	return (cmp_ret < 0);
}

static idx_t	partition(t_data **dataObjects, const idx_t low, const idx_t high) {
	t_data *pivot = dataObjects[high];
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

static void	quickSort(t_data **dataObjects, idx_t low, idx_t high) {
	if (low < high) {
		idx_t partitionIndex = partition(dataObjects, low, high);

		quickSort(dataObjects, low, partitionIndex - 1);
		quickSort(dataObjects, partitionIndex + 1, high);
	}
}

void	sort_dataObjects(t_data **dataObjects, const size_t dataObject_amount) {
	quickSort(dataObjects, 0, (idx_t)(dataObject_amount - 1));
}
