#ifndef MOVEMENT_UTILS_H
# define MOVEMENT_UTILS_H
# include "structs.h"

t_nodes	*get_node(t_maps *map, int x, int y);
void	update_state(t_characters *character, int offset_x, int offset_y);
int		is_blocked(t_maps *map, int x, int y);
void	increase_movement(t_characters *character);
void	you_win(t_nodes *escape);

#endif
