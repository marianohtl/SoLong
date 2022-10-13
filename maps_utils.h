#ifndef MAPS_UTILS_H
# define MAPS_UTILS_H
# include "structs.h"

t_nodes	*new_node(int x, int y, char element);
void	free_file(char *message, int fd, char *content, char *line);
void	validate(int fd, char *content, char *line, t_map_size *map_size);
t_maps	*create_map(int height, int width, char *content);
char	*read_all_file(int file_descriptor, t_map_size *map_size);

#endif
