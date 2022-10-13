#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include "structs.h"

linked_list	*new_linked_list_element(void *content);
void	free_linked_list(linked_list **head);

#endif



