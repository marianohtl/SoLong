/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:34:28 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:34:30 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "structs.h"
#include "movement_utils.h"
#include "mlx.h"

static int	move(t_characters *character, int offset_x, int offset_y)
{
	int		x;
	int		y;
	t_nodes	*node;

	node = get_node(character->map, character->col, character->row);
	if (node->map_item == 'D')
		return (0);
	x = character->col;
	y = character->row;
	if (is_blocked(character->map, x + offset_x, y + offset_y))
		return (0);
	update_state(character, offset_x, offset_y);
	node = get_node(character->map, character->col, character->row);
	increase_movement(character);
	if (character->map->collectible_count == 0 && node->map_item == 'F')
	{
		you_win(node);
		return (0);
	}
	return (1);
}

int	move_right(void *param)
{
	t_characters	*character;

	character = param;
	if (move(param, GRID, 0) == 1)
		character->current = character->right;
	return (0);
}

int	move_left(void *param)
{
	t_characters	*character;

	character = param;
	if (move(param, -GRID, 0) == 1)
		character->current = character->left;
	return (0);
}

int	move_up(void *param)
{
	move(param, 0, -GRID);
	return (0);
}

int	move_down(void *param)
{
	move(param, 0, GRID);
	return (0);
}
