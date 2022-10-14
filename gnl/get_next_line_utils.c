/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:11:15 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:39:55 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	len(const char *s)
{
	size_t	length;

	if (!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		src_length;
	size_t		copy_length;
	size_t		index;

	src_length = len(src);
	if (size != 0)
	{
		copy_length = src_length;
		if (size <= src_length)
			copy_length = size - 1;
		index = 0;
		while (index < copy_length)
		{
			dest[index] = src[index];
			index = index + 1;
		}
		dest[copy_length] = '\0';
	}
	return (src_length);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_src;
	size_t	size_dest;

	size_src = len(src);
	size_dest = len(dest);
	if (size <= size_dest)
		return (size_src + size);
	ft_strlcpy(&dest[size_dest], src, size - size_dest);
	return (size_dest + size_src);
}

char	*join(char *s1, char *s2, size_t n)
{
	char	*concat;

	concat = malloc(n * sizeof(*concat));
	if (concat == NULL)
		return (concat);
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	ft_strlcpy(concat, s1, n);
	ft_strlcat(concat, s2, n);
	return (concat);
}

void	ft_strset(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		str[i++] = '\0';
}
