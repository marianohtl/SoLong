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

int	validate(char *line, int width, int height)
{
	size_t	size;

	size = len(line);
	if (size > 0 && line[size - 1] == '\n')
			size--;
	if (!valid_content(line))
	{
		ft_putstr_fd("Error\nMap has invalid content.\n", STDERR_FILENO);
		exit(1);
	}
	if (size > MAX_WIDTH)
	{
		ft_putstr_fd("Error\nMap has invalid width. Max width is 38 characters.\n", STDERR_FILENO);
		exit(1);
	}
	if (height > MAX_HEIGHT)
	{
		ft_putstr_fd("Error\nMap has invalid height. Max height is 19 lines.\n", STDERR_FILENO);
		exit(1);
	}
	if (size != width)
	{
		ft_putstr_fd("Error\nMap must be rectangular.\n", STDERR_FILENO);
		exit(1);
	}
}

maps	*read_map(const char *file)
{
	int	file_descriptor;
	maps	*map;
	char	*content;
	char	*line;
	int	height;
	int	width;
	int	x;
	int	y;
	int	coord;
	size_t	size;

	content = "";
	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor < 0)
		return (NULL);
	line = "";
	height = 0;
	width = 0;
	size = 0;
	while (line != NULL)
	{
		content = join(content, line, len(content) + size + 1);
		line = get_next_line(file_descriptor);
		size = len(line);
		if (size > 0 && line[size - 1] == '\n')
			size--;
		if (width == 0)
			width = (int) size;
		if (line != NULL)
			validate(line, width, 0);
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
	map->height = height;
	map->width = width;
	return (map);
}
