#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include "structs.h"

t_linked_list	*new_linked_list_element(void *content);
void			free_linked_list(t_linked_list **head);
void			add_node(t_linked_list **head, t_nodes *node);

#endif
