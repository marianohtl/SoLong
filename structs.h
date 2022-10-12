#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_nodes
{
	int		x;
	int		y;
	int		evaluation;
	char	map_item;
	char	visited;
}	nodes;

typedef struct maps
{
	nodes	**content;
	int		height;
	int		width;
	int		collectible_count;
}	maps;

typedef struct linked_list linked_list;
typedef struct linked_list
{
	linked_list	*next;
	nodes	*content;
}	linked_list;

#endif