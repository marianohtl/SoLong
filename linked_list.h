#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include "structs.h"

linked_list	*new_linked_list_element(void *content);
void	delete_element(linked_list **head, linked_list *element);

#endif



