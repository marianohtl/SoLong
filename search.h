#ifndef SEARCH_H
# define SEARCH_H
# include "structs.h"

t_nodes	*new_node(int x, int y, char element);
t_nodes	*search(t_maps *map, t_nodes *start, t_nodes *target);

#endif
