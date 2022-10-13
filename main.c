#include "constants.h"
#include "get_next_line.h"
#include "maps.h"
#include "utils.h"
#include "validation.h"
#include "mlx.h"
#include "mlx_int.h"

typedef struct screens
{
	void *window;
	t_xvar *display;
	int	height;
	int	width;
} screens;

typedef struct backgrounds
{
	t_img *background;
} backgrounds;

typedef struct characters
{
	screens *screen;
	maps	*map;
	t_img *right;
	t_img *left;
	t_img *current;
	t_img *water;
	t_img *hole;
	t_img *wool;
	backgrounds *background;
	int row;
	int col;
	int	movement_count;
} characters;

typedef int (*key_function)(void *param);

void you_win(void)
{
	ft_putstr_fd("Congratulations, you won!!! :)\nPress ESC to exit the game.\n",STDOUT_FILENO);
}

void	free_map(maps *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			free(map->content[y * map->width + x]);
			x++;
		}
		y++;
	}
	free(map->content);
	free(map);
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
			buffer_foreground[pixel] = 0xFF000000 + buffer_background[row * background->width + col + \
				pixel % foreground->width + \
				(pixel / foreground->width) * background->width];
		pixel++;
	}
}

int destroy_display(void *param)
{
	characters	*character;

	character = param;
	mlx_destroy_window(character->screen->display, character->screen->window);
	mlx_destroy_image(character->screen->display, character->background->background);
	mlx_destroy_image(character->screen->display, character->right);
	mlx_destroy_image(character->screen->display, character->left);
	mlx_destroy_image(character->screen->display, character->water);
	mlx_destroy_image(character->screen->display, character->wool);
	mlx_destroy_image(character->screen->display, character->hole);
	mlx_destroy_display(character->screen->display);
	free_map(character->map);
	free(character->screen->display);
	exit(0);
}

int	is_water(maps *map, int x, int y)
{
	return (map->content[map->width * y / GRID + x / GRID]->map_item == '1');
}


void is_collectible(maps *map, int x, int y)
{
	if(map->content[map->width * y / GRID + x / GRID]->map_item == 'C')
	{
		map->content[map->width * y / GRID + x / GRID]->map_item = '0';
		map->collectible_count--;

	}
}

void	increase_movement(characters *character)
{
	character->movement_count++;
	ft_putnbr_fd(character->movement_count, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int exit_game(maps *map, int x, int y)
{
	return (map->collectible_count > 0 && map->content[map->width * y / GRID + x / GRID]->map_item == 'E');
}

int	move_right(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col + GRID, character->row) || exit_game(character->map, character->col + GRID, character->row))
		return (0);
	is_collectible(character->map, character->col + GRID, character->row);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->col += GRID;
	character->current = character->right;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
	increase_movement(character);
	if (character->map->content[character->map->width * character->row / GRID + character->col / GRID]->map_item == 'E')
	{
		you_win();
	}
	
}
int	move_left(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col - GRID, character->row) || exit_game(character->map, character->col - GRID, character->row))
		return (0);
	is_collectible(character->map, character->col - GRID, character->row);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->col -= GRID;
	character->current = character->left;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
	increase_movement(character);
	if (character->map->content[character->map->width * character->row / GRID + character->col / GRID]->map_item == 'E')
	{
		you_win();
	}
}

int	move_up(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col, character->row - GRID) || exit_game(character->map, character->col , character->row - GRID))
		return (0);
	is_collectible(character->map, character->col, character->row - GRID);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->row -= GRID;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
	increase_movement(character);
	if (character->map->content[character->map->width * character->row / GRID + character->col / GRID]->map_item == 'E')
	{
		you_win();
	}
}

int	move_down(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col, character->row + GRID) || exit_game(character->map, character->col , character->row + GRID))
		return (0);
	is_collectible(character->map, character->col, character->row + GRID);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->row += GRID;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
	increase_movement(character);
	if (character->map->content[character->map->width * character->row / GRID + character->col / GRID]->map_item == 'E')
	{
		you_win();
	}
}

int	key_delegator(int key_code, void *param)
{
	static	key_function functions[65536];

	if (functions[XK_Q] == NULL)
	{
		functions[XK_Q] = &destroy_display;
		functions[XK_q] = &destroy_display;
		functions[XK_Escape] = &destroy_display;
		functions[XK_Right] = &move_right;
		functions[XK_D] = &move_right;
		functions[XK_d] = &move_right;
		functions[XK_Left] = &move_left;
		functions[XK_A] = &move_left;
		functions[XK_a] = &move_left;
		functions[XK_Up] = &move_up;
		functions[XK_W] = &move_up;
		functions[XK_w] = &move_up;
		functions[XK_Down] = &move_down;
		functions[XK_S] = &move_down;
		functions[XK_s] = &move_down;
	}
	if (functions[key_code] == NULL)
		return (0);
	return (functions[key_code](param));
}

int	fill_map(screens *screen, maps *map, characters *character, t_img *grass, t_img *water, t_img *wool, t_img *hole)
{
	int	row;
	int	col;
	nodes	*node;
	int	pixels_x;
	int	pixels_y;

	map->collectible_count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			node = map->content[row * map->width + col];
			pixels_x = col * GRID;
			pixels_y = row * GRID;
			if (node->map_item == '1')
				mlx_put_image_to_window(screen->display, screen->window, water, pixels_x, pixels_y);
			else
				mlx_put_image_to_window(screen->display, screen->window, grass, pixels_x, pixels_y);
			
			if(node->map_item == 'C')
			{
				mlx_put_image_to_window(screen->display, screen->window, wool, pixels_x, pixels_y);
				map->collectible_count += 1;
			}
			if(node->map_item == 'E')
				mlx_put_image_to_window(screen->display, screen->window, hole, pixels_x, pixels_y);
			if (node->map_item == 'P')
			{
				character->col = pixels_x;
				character->row = pixels_y;
				mlx_put_image_to_window(screen->display, screen->window, character->current, pixels_x, pixels_y);
			}
			col++;
		}
		row++;
	}
}

int	update_window(void *param)
{
	characters	*character;

	character = param;
	fill_map(character->screen, character->map, character, character->background->background, character->water, character->wool, character->hole);
}

int	main(int argc, char **argv)
{
	void* display;
	void* window;
	screens screen;
	characters character;
	backgrounds background;
	t_img	*water;
	t_img	*wool;
	t_img	*hole;
	int	height;
	int	width;
	int	start_row;
	int	start_col;
	maps	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments. Program takes only the map file name as parameter.\n", STDERR_FILENO);
		exit(1);
	}
	if (ft_strncmp(argv[1] + len(argv[1]) - 4, ".ber", 5) != 0)
	{
		ft_putstr_fd("Error\nMap file name must end with '*.ber' extension.\n", STDERR_FILENO);
		exit(1);
	}
	map = read_map(argv[1]);
	validate_map(map);
	screen.height = map->height * GRID;
	screen.width = map->width * GRID;
	display = mlx_init();
	window = mlx_new_window(display, screen.width , screen.height, "Deletinho");
	screen.display = display;
	screen.window = window;

	background.background = mlx_xpm_file_to_image(display,"./images/xpm/sand.xpm", &width, &height);
	water = mlx_xpm_file_to_image(display, "./images/xpm/water.xpm", &width, &height);
	wool = mlx_xpm_file_to_image(display, "./images/xpm/wool.xpm", &width, &height);
	hole = mlx_xpm_file_to_image(display, "./images/xpm/hole.xpm", &width, &height);
	character.right = mlx_xpm_file_to_image(display,"./images/xpm/right_cat.xpm", &width, &height);
	character.left = mlx_xpm_file_to_image(display,"./images/xpm/left_cat.xpm", &width, &height);
	merge_image(background.background, wool, 0, 0);
	merge_image(background.background, hole, 0, 0);
	merge_image(background.background, character.right, 0, 0);
	merge_image(background.background, character.left, 0, 0);
	character.current = character.right;
	character.background = &background;
	character.screen = &screen;
	character.map = map;
	character.movement_count = 0;
	character.water = water;
	character.wool = wool;
	character.hole = hole;

	fill_map(&screen, map, &character, background.background, water, wool, hole);
	mlx_key_hook(window, &key_delegator, &character);
	mlx_hook(window, DestroyNotify, 0, &destroy_display, &character);
	mlx_loop_hook(display, &update_window, &character);
	mlx_loop(display);
	return(0);
}
