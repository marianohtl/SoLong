#include "structs.h"
#include <stdlib.h>

t_linked_list	*new_linked_list_element(void *content)
{
	t_linked_list	*element;

	element = malloc(sizeof(*element));
	element->next = NULL;
	element->content = content;
	return (element);
}

void	free_linked_list(t_linked_list **head)
{
	t_linked_list	*previous;
	t_linked_list	*current;

	if (*head == NULL)
		return ;
	current = *head;
	previous = NULL;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
		free(previous);
	}
	free(current);
	*head = NULL;
}

void	add_node(t_linked_list **head, t_nodes *node)
{
	t_linked_list	*start;

	if (node == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_linked_list_element(node);
		return ;
	}
	start = new_linked_list_element(node);
	start->next = *head;
	*head = start;
}
