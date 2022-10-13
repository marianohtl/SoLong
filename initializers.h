#ifndef INITIALIZERS_H
# define INITIALIZERS_H
# include "structs.h"

void	initialize_screen(t_screens *screen, t_maps *map);
void	initialize_character(t_characters *character, t_maps *map, \
	t_screens *screen);

#endif
