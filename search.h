#ifndef SEARCH_H
# define SEARCH_H
typedef struct s_nodes nodes;
typedef struct s_nodes
{
	int		x;
	int		y;
	int		evaluation;
	char	map_item;
	char	visited;
}	nodes;
#endif
