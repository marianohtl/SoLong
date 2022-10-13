#include "maps.h"
#include "validation.h"
#include <stdio.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

t_nodes	*search(t_maps *map, t_nodes *start, t_nodes *target);

void	check_map(t_maps *map, t_nodes *start, t_nodes *target)
{
	if (search(map, start, target) == NULL)
	{
		printf(RED"Path NOT found.\n"RESET);
		return ;
	}
	printf(GREEN"Path found.\n"RESET);
}

int	main(void)
{
	t_maps	*map;


	map = read_map("maps/test_map.ber");
	check_map(map, map->content[40], map->content[45]);
	map = read_map("maps/test_map.ber");
	check_map(map, map->content[40], map->content[27]);
	map = read_map("maps/test_map.ber");
	check_map(map, map->content[40], map->content[39]);
	return (0);
}
