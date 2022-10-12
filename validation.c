#include "constants.h"
#include "get_next_line.h"
#include "structs.h"
#include "search.h"
#include "utils.h"


int	valid_content(char *line)
{
	while (ft_strchr("01CEP", *line) != NULL)
		line++;
	return (*line == '\n' || *line == '\0');
}

int	valid_width(char *line, int width)
{
	size_t	length;

	length = len(line);
	return (length == width && length <= MAX_WIDTH);
}

void	clean_map_visit(maps *map)
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

void	validate_map(maps *map)
{
	nodes	*start;
	nodes	*target;
	nodes	*node;
	const int first_row = 0;
	const int last_row = map->height - 1;
	const int first_column = 0;
	const int last_column = map->width - 1;
	int		x;
	int		y;

	start = NULL;
	target = NULL;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			node = map->content[x + y * map->width];
			if((first_row == y || first_column == x || last_row == y || last_column == x) && node->map_item != '1')
			{
				ft_putstr_fd("Error\nMap must be surrounded by walls.\n", STDERR_FILENO);
				exit(1);
			}
			if ((start != NULL && node->map_item == 'P') || (target != NULL && node->map_item == 'E'))
			{
				ft_putstr_fd("Error\nMap has multiples starting positions or exits.\n", STDERR_FILENO);
				exit(1);
			}
			if (node->map_item == 'P')
				start = node;
			else if (node->map_item == 'E')
				target = node;
			x++;
		}
		y++;
	}
	if (search(map, start, target) == NULL)
	{
		ft_putstr_fd("Error\nMap must have a valid path to exit.\n", STDERR_FILENO);
		exit(1);
	}
	y = 0;
	target = NULL;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			node = map->content[x + y * map->width];
			if (node->map_item == 'C')
			{
				clean_map_visit(map);
				target = node;
			}
			if (node->map_item == 'C' && search(map, start, node) == NULL)
			{
				ft_putstr_fd("Error\nMap must have a valid path to each collectible.\n", STDERR_FILENO);
				exit(1);
			}
			x++;
		}
		y++;
	}
	if (target == NULL)
	{
		ft_putstr_fd("Error\nMap must have at least one collectible.\n", STDERR_FILENO);
		exit(1);
	}
}