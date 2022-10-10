#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include "validation.h"

typedef struct linked_list linked_list;
typedef struct linked_list
{
	linked_list	*next;
	nodes	*content;
}	linked_list;

linked_list	*new_linked_list_element(void *content);
void	delete_element(linked_list **head, linked_list *element);

#endif



