#ifndef MAPS_H
# define MAPS_H
# include "structs.h"

void	free_map(t_maps *map, int limit);
void	clean_map_visit(t_maps *map);
t_maps	*read_map(const char *file);
void	fill_map(t_maps *map, t_characters *character);

#endif
