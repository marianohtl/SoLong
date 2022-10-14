#include "validation.h"
#include "maps.h"
#include "linked_list.h"
#include "search_utils.h"
#include <stdlib.h>

t_nodes	*new_node(int x, int y, char element)
{
	t_nodes	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->x = x;
	node->y = y;
	node->map_item = element;
	node->visited = 0;
	return (node);
}

int	distance(int x, int y, int target_x, int target_y)
{
	return ((x - target_x) * (x - target_x) + (y - target_y) * (y - target_y));
}

t_nodes	*evaluate_node(t_nodes *current, t_nodes *target)
{
	if (current->map_item == '1' || current->visited == 1)
		return (NULL);
	current->evaluation = distance(current->x, current->y, \
		target->x, target->y);
	return (current);
}

void	call_evaluate_node(t_maps *map, t_nodes *target, t_nodes *current, \
	t_linked_list **to_visit)
{
	t_nodes	*node;

	node = map->content[current->y * map->width + current->x + 1];
	add_node(to_visit, evaluate_node(node, target));
	node = map->content[current->y * map->width + current->x - 1];
	add_node(to_visit, evaluate_node(node, target));
	node = map->content[(current->y + 1) * map->width + current->x];
	add_node(to_visit, evaluate_node(node, target));
	node = map->content[(current->y - 1) * map->width + current->x];
	add_node(to_visit, evaluate_node(node, target));
}

t_nodes	*search(t_maps *map, t_nodes *start, t_nodes *target)
{
	t_nodes			*current;
	t_linked_list	*to_visit;

	to_visit = NULL;
	current = start;
	current->evaluation = distance(current->x, current->y, target->x, \
		target->y);
	current->visited = 1;
	while (current->evaluation != 0)
	{
		call_evaluate_node(map, target, current, &to_visit);
		current = find_minimum_evaluation(&to_visit);
		if (current == NULL)
			return (NULL);
		current->visited = 1;
	}
	free_linked_list(&to_visit);
	return (current);
}
