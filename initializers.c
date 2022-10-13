#include "constants.h"
#include "structs.h"
#include "mlx.h"

void	merge_image(t_img *background, t_img *foreground, int row, int col)
{
	int	*buffer_background;
	int	*buffer_foreground;
	int	pixel;

	buffer_background = (int *) background->data;
	buffer_foreground = (int *) foreground->data;
	pixel = 0;
	while (pixel < foreground->width * foreground->height)
	{
		if ((buffer_foreground[pixel] & 0xFF000000) == 0xFF000000)
			buffer_foreground[pixel] = buffer_background[pixel];
		pixel++;
	}
}

void	initialize_screen(t_screens *screen, t_maps *map)
{
	screen->height = map->height * GRID;
	screen->width = map->width * GRID;
	screen->display = mlx_init();
	screen->window = mlx_new_window(screen->display, screen->width, \
		screen->height, GAME_TITLE);
}

void	initialize_character(t_characters *character, t_maps *map, \
	t_screens *screen)
{
	int		x;
	int		y;
	void	*display;

	display = screen->display;
	character->background = mlx_xpm_file_to_image(display, SAND, &x, &y);
	character->water = mlx_xpm_file_to_image(display, WATER, &x, &y);
	character->wool = mlx_xpm_file_to_image(display, WOOL, &x, &y);
	character->hole = mlx_xpm_file_to_image(display, HOLE, &x, &y);
	character->right = mlx_xpm_file_to_image(display, RIGHT_CAT, &x, &y);
	character->escape = mlx_xpm_file_to_image(display, ESCAPE_CAT, &x, &y);
	character->left = mlx_xpm_file_to_image(display, LEFT_CAT, &x, &y);
	merge_image(character->hole, character->escape, 0, 0);
	merge_image(character->background, character->escape, 0, 0);
	merge_image(character->background, character->wool, 0, 0);
	merge_image(character->background, character->hole, 0, 0);
	merge_image(character->background, character->right, 0, 0);
	merge_image(character->background, character->left, 0, 0);
	character->current = character->right;
	character->screen = screen;
	character->map = map;
	character->movement_count = 0;
}
