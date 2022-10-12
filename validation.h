#ifndef VALIDATION_H
# define VALIDATION_H
# include "structs.h"

int	valid_content(char *line);
int	valid_width(char *line, int width);
void	validate_map(maps *map);

#endif
