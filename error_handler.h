#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

void	map_error(t_maps *map, char *message, void (*free_map)(t_maps *));
void	quit_program(char *message);
void	system_error(char *message);

#endif
