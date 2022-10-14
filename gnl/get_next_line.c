/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:11:15 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:39:18 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static ssize_t	ft_strchri(const char *string, int c)
{
	ssize_t	index;
	char	convert_c;

	convert_c = (char) c;
	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] == convert_c)
			return (index);
		index++;
	}
	if (string[index] == convert_c)
		return (index);
	return (-1);
}

static char	*clean_set(char **old_adress, char *new_adress)
{
	char	*clean;

	clean = *old_adress;
	*old_adress = new_adress;
	free(clean);
	return (*old_adress);
}

static char	*initialize_buffer(int fd, char *buffer)
{
	if ((fd < 0) || (BUFFER_SIZE < 1) || (read(fd, buffer, 0) < 0))
		return (NULL);
	if (!buffer)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
		if (!buffer)
			return (NULL);
		ft_strset(buffer, BUFFER_SIZE + 1);
	}
	return (buffer);
}

static char	*new_line(char **buffer, char **next, int has_new_line,
	int read_bytes)
{
	char	*concat;

	concat = join(*next, *buffer, len(*next) + has_new_line + 2);
	clean_set(next, concat);
	if (!*next)
		return (NULL);
	ft_strlcpy(*buffer, &(*buffer)[has_new_line + 1],
		read_bytes - (size_t)has_new_line);
	ft_strset(&(*buffer)[read_bytes - (size_t)has_new_line], has_new_line + 1);
	return (*next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next;
	size_t		read_bytes;
	int			has_new_line;

	buffer = initialize_buffer(fd, buffer);
	if (fd < 0 || !buffer)
		return (NULL);
	read_bytes = BUFFER_SIZE;
	next = NULL;
	while (read_bytes >= BUFFER_SIZE)
	{
		if (len(buffer) == 0)
			read_bytes = read(fd, buffer, BUFFER_SIZE);
		has_new_line = ft_strchri(buffer, '\n');
		if (has_new_line != -1)
			return (new_line(&buffer, &next, has_new_line, read_bytes));
		if (!(clean_set(&next, join(next, buffer, len(next) + read_bytes + 1))))
			return (NULL);
		ft_strset(buffer, BUFFER_SIZE + 1);
	}
	clean_set(&buffer, NULL);
	if (len(next) == 0)
		clean_set(&next, NULL);
	return (next);
}
