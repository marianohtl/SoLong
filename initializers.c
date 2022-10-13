#include "constants.h"
#include "structs.h"
#include "maps.h"
#include "error_handler.h"
#include "mlx.h"

void	free_image(void	*display, void *image)
{
	if (image != NULL)
		mlx_destroy_image(display, image);
}

void	free_resources(t_characters *character)
{
	mlx_destroy_window(character->screen->display, character->screen->window);
	free_image(character->screen->display, character->sand);
	free_image(character->screen->display, character->escape);
	free_image(character->screen->display, character->right);
	free_image(character->screen->display, character->left);
	free_image(character->screen->display, character->water);
	free_image(character->screen->display, character->wool);
	free_image(character->screen->display, character->hole);
	mlx_destroy_display(character->screen->display);
	free_map(character->map, \
		character->map->width * character->map->height + 1);
	free(character->screen->display);
}

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
	if (screen->display == NULL)
		return ;
	screen->window = mlx_new_window(screen->display, screen->width, \
		screen->height, GAME_TITLE);
}

void	initialize_character(t_characters *character, t_maps *map, \
	t_screens *screen)
{
	int	i;

	character->screen = screen;
	character->map = map;
	character->movement_count = 0;
	character->sand = mlx_xpm_file_to_image(screen->display, SAND, &i, &i);
	character->water = mlx_xpm_file_to_image(screen->display, WATER, &i, &i);
	character->wool = mlx_xpm_file_to_image(screen->display, WOOL, &i, &i);
	character->hole = mlx_xpm_file_to_image(screen->display, HOLE, &i, &i);
	character->right = mlx_xpm_file_to_image(screen->display, R_CAT, &i, &i);
	character->escape = mlx_xpm_file_to_image(screen->display, E_CAT, &i, &i);
	character->left = mlx_xpm_file_to_image(screen->display, L_CAT, &i, &i);
	if (!(character->right && character->water && character->hole && character \
		->sand && character->wool && character->left && character->escape))
	{
		free_resources(character);
		quit_program("Failed to load all the images.\n");
	}
	merge_image(character->hole, character->escape, 0, 0);
	merge_image(character->sand, character->escape, 0, 0);
	merge_image(character->sand, character->wool, 0, 0);
	merge_image(character->sand, character->hole, 0, 0);
	merge_image(character->sand, character->right, 0, 0);
	merge_image(character->sand, character->left, 0, 0);
	character->current = character->right;
}
