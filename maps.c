#include "constants.h"
#include "structs.h"
#include "get_next_line.h"
#include "utils.h"
#include "validation.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


nodes	*new_node(int x, int y, char element)
{
	nodes	*node;

	node = malloc(sizeof(*node));
	node->x = x;
	node->y = y;
	node->map_item = element;
	node->visited = 0;
	return (node);
}


void	free_map(maps *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			free(map->content[y * map->width + x]);
			x++;
		}
		y++;
	}
	free(map->content);
	free(map);
}

int	validate(int fd, char *content, char *line, int width, int height)
{
	size_t	size;

	size = len(line);
	if (size > 0 && line[size - 1] == '\n')
			size--;
	if (!valid_content(line))
	{
		ft_putstr_fd("Error\nMap has invalid content.\n", STDERR_FILENO);
		free(content);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		exit(1);
	}
	if (size > MAX_WIDTH)
	{
		ft_putstr_fd("Error\nMap has invalid width. Max width is 38 characters.\n", STDERR_FILENO);
		free(content);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		exit(1);
	}
	if (height > MAX_HEIGHT)
	{
		ft_putstr_fd("Error\nMap has invalid height. Max height is 19 lines.\n", STDERR_FILENO);
		free(content);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		exit(1);
	}
	if (size != width)
	{
		ft_putstr_fd("Error\nMap must be rectangular.\n", STDERR_FILENO);
		free(content);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		exit(1);
	}
}

maps	*read_map(const char *file)
{
	int	file_descriptor;
	maps	*map;
	char	*content;
	char	*temp;
	char	*line;
	int	height;
	int	width;
	int	x;
	int	y;
	int	coord;
	size_t	size;

	content = NULL;
	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor < 0)
		return (NULL);
	line = "";
	height = 0;
	width = 0;
	size = 0;
	while (line != NULL)
	{
		temp = content;
		if (content == NULL)
			content = "";
		content = join(content, line, len(content) + size + 1);
		if (*line != '\0')
			free(line);
		free(temp);
		line = get_next_line(file_descriptor);
		size = len(line);
		if (size > 0 && line[size - 1] == '\n')
			size--;
		if (width == 0)
			width = (int) size;
		if (line != NULL)
			validate(file_descriptor, content, line, width, 0);
		if (size > 0)
			height++;
	}
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
	free(content);
	map->height = height;
	map->width = width;
	return (map);
}
