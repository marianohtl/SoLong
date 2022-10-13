#include "structs.h"
#include <stdlib.h>

linked_list	*new_linked_list_element(void *content)
{
	linked_list *element;

	element = malloc(sizeof(*element));
	element->next = NULL;
	element->content = content;
	return (element);
}

void	free_linked_list(linked_list **head)
{
	linked_list	*previous;
	linked_list	*current;

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
