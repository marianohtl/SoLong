#include "maps.h"
#include "validation.h"
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
	while (line != NULL)
	{
		size = len(line);
		if (size > 0 && line[size - 1] == '\n')
			size--;
		content = join(content, line, len(content) + size + 1);
		line = get_next_line(file_descriptor);
		if (width == 0)
			width = (int) size;
		if (line != NULL && size == width)
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
