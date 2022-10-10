#include "validation.h"
#include "maps.h"
#include "linked_list.h"
#include <stdlib.h>


int	distance(int x, int y, int target_x, int target_y)
{
	return (x - target_x) * (x - target_x) + (y - target_y) * (y - target_y);
}

void	add_node(linked_list **head, linked_list **last, nodes *node)
{
	if (node == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_linked_list_element(node);
		*last = *head;
		return ;
	}
	(*last)->next = new_linked_list_element(node);
	*last = (*last)->next;
}

nodes	*find_minimum_evaluation(linked_list **head, linked_list **last)
{
	linked_list	*minimum;
	linked_list	*element;
	linked_list	*previous;
	linked_list	*temp;

	if (*head == NULL)
		return (NULL);
	previous = NULL;
	element = *head;
	minimum = element;
	while (element->next != NULL)
	{
		temp = element;
		element = element->next;
		if (element->content->evaluation < minimum->content->evaluation)
		{
			previous = temp;
			minimum = element;
		}
	}
	if (previous == NULL)
	{
		*head = minimum->next;
		return (minimum->content);
	}
	if (minimum == *last)
		*last = previous;
	previous->next = minimum->next;
	return (minimum->content);
}

void evaluate_node(maps *map, nodes *target, nodes *current, linked_list **to_visit, linked_list **last, int x, int y)
{
	nodes	*node;
	int coord;

	coord = current->x + x + (current->y + y ) * map->width;
	node = map->content[coord];
	if (node->map_item == '1' || node->visited == 1)
		return ;
	node->evaluation = distance(node->x,node->y, target->x, target->y);
	add_node(to_visit, last, node);
}

void call_evaluate_node(maps *map, nodes *target, nodes *current, linked_list **to_visit, linked_list **last)
{
	evaluate_node(map, target, current, to_visit, last, 1 , 0);
	evaluate_node(map, target, current, to_visit, last, -1 , 0);
	evaluate_node(map, target, current, to_visit, last, 0 , 1);
	evaluate_node(map, target, current, to_visit, last, 0 , -1);

}


nodes	*search(maps *map, nodes *start, nodes *target)
{
	nodes	*current;
	linked_list	*to_visit;
	linked_list	*last;

	to_visit = NULL;
	last = NULL;
	current = start;
	current->evaluation = distance(current->x, current->y, target->x, target->y);
	current->visited = 1;
	while (current->evaluation != 0)
	{
		call_evaluate_node(map, target, current, &to_visit, &last);
		current = find_minimum_evaluation(&to_visit, &last);
		if (current == NULL)
			return (NULL);
		current->visited = 1;
	}
	return (current);
}
