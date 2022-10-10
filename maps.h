#ifndef MAPS_H
# define MAPS_H
# include "get_next_line.h"
# include "validation.h"

typedef struct maps
{
	nodes	**content;
	int		height;
	int		width;
}	maps;

maps	*read_map(const char *file);

#endif


