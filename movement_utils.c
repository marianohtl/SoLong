#include "constants.h"
#include "structs.h"
#include "utils.h"
#include <unistd.h>

t_nodes	*get_node(t_maps *map, int x, int y)
{
	return (map->content[map->width * y / GRID + x / GRID]);
}

void	update_state(t_characters *character, int offset_x, int offset_y)
{
	t_nodes	*node;

	node = get_node(character->map, character->col, character->row);
	if (node->map_item == 'F')
		node->map_item = 'E';
	else
		node->map_item = '0';
	character->col += offset_x;
	character->row += offset_y;
	node = get_node(character->map, character->col, character->row);
	if (node->map_item == 'C')
		character->map->collectible_count--;
	if (node->map_item == 'E')
		node->map_item = 'F';
	else
		node->map_item = 'P';
}

int	is_blocked(t_maps *map, int x, int y)
{
	t_nodes	*node;

	node = get_node(map, x, y);
	return (node->map_item == '1');
}

void	increase_movement(t_characters *character)
{
	character->movement_count++;
	ft_putnbr_fd(character->movement_count, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	you_win(t_nodes *escape)
{
	escape->map_item = 'D';
	ft_putstr_fd("Congratulations, you won!!! :)\n" \
		"Press ESC to exit the game.\n", STDOUT_FILENO);
}
