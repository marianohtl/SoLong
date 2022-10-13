#include "constants.h"
#include "structs.h"
#include "get_next_line.h"
#include "utils.h"
#include "validation.h"
#include <stdlib.h>
#include <fcntl.h>

t_nodes	*new_node(int x, int y, char element)
{
	t_nodes	*node;

	node = malloc(sizeof(*node));
	node->x = x;
	node->y = y;
	node->map_item = element;
	node->visited = 0;
	return (node);
}

void	file_error(char *message, int fd, char *content, char *line)
{
	free(content);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	exit(1);
}

void	validate(int fd, char *content, char *line, t_map_size *map_size)
{
	size_t	length;

	length = len(line);
	if (length > 0 && line[length - 1] == '\n')
			length--;
	if (!valid_content(line))
		file_error("Map has invalid content.\n", fd, content, line);
	if (length > MAX_WIDTH)
		file_error("Map has invalid width. Max width is 38 characters.\n", fd, \
			content, line);
	if (map_size->height > MAX_HEIGHT)
		file_error("Map has invalid height. Max height is 19 lines.\n", fd, \
			content, line);
	if (length != map_size->width)
		file_error("Map must be rectangular.\n", fd, content, line);
}

t_maps	*create_map(int height, int width, char *content)
{
	t_maps	*map;
	int		x;
	int		y;
	int		coord;

	map = malloc(sizeof(*map));
	if (map == NULL)
		return (NULL);
	map->content = malloc(sizeof(*(map->content)) * height * width);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			coord = x + y * width;
			map->content[coord] = new_node(x, y, content[coord]);
			x++;
		}
		y++;
	}
	map->height = height;
	map->width = width;
}

char	*read_all_file(int file_descriptor, t_map_size *map_size)
{
	char	*content;
	char	*temp;
	char	*line;
	size_t	length;

	content = NULL;
	line = get_next_line(file_descriptor);
	while (line != NULL)
	{
		temp = content;
		length = len(line);
		if (length > 0 && line[length - 1] == '\n')
			length--;
		if (map_size->width == 0)
			map_size->width = (int) length;
		if (length > 0)
			(map_size->height)++;
		if (line != NULL)
			validate(file_descriptor, content, line, map_size);
		content = join(content, line, len(content) + length + 1);
		free(line);
		free(temp);
		line = get_next_line(file_descriptor);
	}
	return (content);
}
