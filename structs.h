/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:13 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:35:14 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "mlx_int.h"

typedef struct s_nodes
{
	int		x;
	int		y;
	int		evaluation;
	char	map_item;
	char	visited;
}	t_nodes;

typedef struct s_maps
{
	t_nodes	**content;
	int		height;
	int		width;
	int		collectible_count;
}	t_maps;

typedef struct s_linked_list	t_linked_list;
typedef struct s_linked_list
{
	t_linked_list	*next;
	t_nodes			*content;
}	t_linked_list;

typedef struct s_screens
{
	void	*window;
	t_xvar	*display;
	int		height;
	int		width;
}	t_screens;

typedef struct s_characters
{
	t_screens	*screen;
	t_maps		*map;
	t_img		*right;
	t_img		*left;
	t_img		*current;
	t_img		*water;
	t_img		*hole;
	t_img		*wool;
	t_img		*escape;
	t_img		*sand;
	int			row;
	int			col;
	int			movement_count;
}	t_characters;

typedef struct s_map_size
{
	int	height;
	int	width;
}	t_map_size;

#endif
