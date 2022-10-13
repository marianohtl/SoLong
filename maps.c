#include "constants.h"
#include "structs.h"
#include "get_next_line.h"
#include "utils.h"
#include "maps_utils.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	clean_map_visit(t_maps *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->content[x + y * map->width]->visited = 0;
			x++;
		}
		y++;
	}
}

void	free_map(t_maps *map)
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

t_maps	*read_map(const char *file)
{
	int			file_descriptor;
	t_maps		*map;
	char		*content;
	t_map_size	map_size;

	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor < 0)
		return (NULL);
	map_size.height = 0;
	map_size.width = 0;
	content = read_all_file(file_descriptor, &map_size);
	map = create_map(map_size.height, map_size.width, content);
	free(content);
	return (map);
}

void	fill_node(t_nodes *node, t_characters *character, int x, int y)
{
	if (node->map_item == '1')
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->water, x, y);
	else if (node->map_item == '0')
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->background, x, y);
	else if (node->map_item == 'C')
	{
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->wool, x, y);
		character->map->collectible_count++;
	}
	else if (node->map_item == 'E')
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->hole, x, y);
	else if (node->map_item == 'P')
	{
		character->col = x;
		character->row = y;
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->current, x, y);
	}
	else if (node->map_item == 'D')
		mlx_put_image_to_window(character->screen->display, \
			character->screen->window, character->escape, x, y);
}

void	fill_map(t_maps *map, t_characters *character)
{
	int		row;
	int		col;

	map->collectible_count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			fill_node(map->content[row * map->width + col], character, \
				col * GRID, row * GRID);
			col++;
		}
		row++;
	}
}
