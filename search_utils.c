#include "linked_list.h"
#include "structs.h"

t_nodes	*extract_node(t_linked_list **head, t_linked_list *previous, \
	t_linked_list *minimum)
{
	t_nodes	*result;

	if (previous == NULL)
	{
		*head = minimum->next;
		result = minimum->content;
		free(minimum);
		return (result);
	}
	previous->next = minimum->next;
	result = minimum->content;
	free(minimum);
	return (result);
}

t_nodes	*find_minimum_evaluation(t_linked_list **head)
{
	t_linked_list	*minimum;
	t_linked_list	*element;
	t_linked_list	*previous;
	t_linked_list	*temp;

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
	return (extract_node(head, previous, minimum));
}
