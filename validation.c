/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:28 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:35:28 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "get_next_line.h"
#include "structs.h"
#include "error_handler.h"
#include "maps.h"
#include "search.h"
#include "utils.h"

int	valid_content(char *line)
{
	while (ft_strchr("01CEP", *line) != NULL)
		line++;
	return (*line == '\n' || *line == '\0');
}

void	validate_collectible(t_maps *map, t_nodes *start, int x, int y)
{
	t_nodes	*node;

	node = map->content[x + y * map->width];
	if (node->map_item == 'C')
	{
		clean_map_visit(map);
		node = search(map, start, node);
		if (node == NULL)
			map_error(map, map->width * map->height + 1, \
				"Map must have a valid path to each collectible.\n", &free_map);
	}
}

void	validate_collectibles(t_maps *map, t_nodes *start)
{
	int		x;
	int		y;
	int		has_collectible;

	y = 0;
	has_collectible = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->content[x + y * map->width]->map_item == 'C')
				has_collectible = 1;
			validate_collectible(map, start, x, y);
			x++;
		}
		y++;
	}
	if (!has_collectible)
		map_error(map, map->width * map->height + 1, \
			"Map must have at least one collectible.\n", &free_map);
}

void	validate_start_and_exit(t_maps *map, t_nodes **start, t_nodes **target)
{
	t_nodes	*node;
	int		x;
	int		y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			node = map->content[x + y * map->width];
			if ((y == 0 || x == 0 || y == map->height - 1 || \
				x == map->width - 1) && node->map_item != '1')
				map_error(map, map->width * map->height + 1, \
					"Map must be surrounded by walls.\n", &free_map);
			if ((*start != NULL && node->map_item == 'P') || \
				(*target != NULL && node->map_item == 'E'))
				map_error(map, map->width * map->height + 1, \
					"Map has multiple start or exits.\n", &free_map);
			if (node->map_item == 'P')
				*start = node;
			else if (node->map_item == 'E')
				*target = node;
		}
	}
}

void	validate_map(t_maps *map)
{
	t_nodes		*start;
	t_nodes		*target;
	t_nodes		*node;

	start = NULL;
	target = NULL;
	validate_start_and_exit(map, &start, &target);
	if (start == NULL)
		map_error(map, map->width * map->height + 1, \
			"Map must have one starting position.\n", &free_map);
	if (target == NULL)
		map_error(map, map->width * map->height + 1, \
			"Map must have one exit.\n", &free_map);
	node = search(map, start, target);
	if (node == NULL)
		map_error(map, map->width * map->height + 1, \
			"Map must have a valid path to exit.\n", &free_map);
	validate_collectibles(map, start);
}
