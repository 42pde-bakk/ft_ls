//
// Created by peer on 12-11-22.
//
#include "libft.h"
#include "data_obj.h"

char	*ft_str3join(const char *a, const char *b, const char *c) {
	char			*out;
	const size_t	len_a = ft_strlen(a),
			len_b = ft_strlen(b),
			len_c = ft_strlen(c);
	const size_t	total_length = len_a + len_b + len_c + 1;

	out = calloc(total_length, sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, a, len_a + 1);
	ft_strlcpy(out + len_a, b, len_b + 1);
	ft_strlcpy(out + len_a + len_b, c, len_c + 1);
	return (out);
}
