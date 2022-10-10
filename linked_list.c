#include "linked_list.h"
#include <stdlib.h>

linked_list	*new_linked_list_element(void *content)
{
	linked_list *element;

	element = malloc(sizeof(*element));
	element->next = NULL;
	element->content = content;
	return (element);
}

void	delete_element(linked_list **head, linked_list *element)
{
	linked_list	*previous;
	linked_list	*current;

	previous = NULL;
	current = *head;
	while (current->next != NULL)
	{
		if (current == element)
		{
			if (previous == NULL)
			{
				*head = current->next;
				return ;
			}
			previous->next = current->next;
			return ;
		}
		current = current->next;
	}
	if (current == element)
	{
		if (previous == NULL)
		{
			*head = current->next;
			return ;
		}
		previous->next = current->next;
		return ;
	}
}