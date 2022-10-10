#include "get_next_line.h"
#include"mlx.h"
#include"mlx_int.h"
#define GRID 76

typedef struct maps
{
	char	*content;
	int	height;
	int	width;
}	maps;

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
	backgrounds *background;
	int row;
	int col;
} characters;

typedef int (*key_function)(void *param);

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
	screens	*screen;

	screen = param;
	mlx_loop_end(screen->display);
	mlx_destroy_window(screen->display, screen->window);
}

int	is_water(maps *map, int x, int y)
{
	return (map->content[map->width * y / GRID + x / GRID] == '1');
}

int	move_right(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col + GRID, character->row))
		return (0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->col += GRID;
	character->current = character->right;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}
int	move_left(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col - GRID, character->row))
		return (0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->col -= GRID;
	character->current = character->left;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}

int	move_up(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col, character->row - GRID))
		return (0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->row -= GRID;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}

int	move_down(void *param)
{
	characters	*character;

	character = param;
	if (is_water(character->map, character->col, character->row + GRID))
		return (0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, character->col, character->row);
	character->row += GRID;
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
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

maps	*read_map(char *file)
{
	int	file_descriptor;
	maps	*map;
	char	*content;
	char	*line;
	int	height;
	int	width;
	size_t	size;

	content = "";
	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor < 0)
		return (NULL);
	line = "";
	height = 0;
	width = 0;
	while (line != NULL)
	{
		size = len(line);
		if (size > 0 && line[size - 1] == '\n')
			size--;
		content = join(content, line, len(content) + size + 1);
		line = get_next_line(file_descriptor);
		if (width == 0)
			width = (int) size;
		if (line != NULL && size == width)
			height++;
	}
	map = malloc(sizeof(*map));
	if (map == NULL)
		return (NULL);
	map->content = content;
	map->height = height;
	map->width = width;
	return (map);
}

int	fill_map(screens *screen, maps *map, characters *character, t_img *grass, t_img *water, t_img *wool, t_img *hole)
{
	int	row;
	int	col;
	char	cell;
	int	pixels_x;
	int	pixels_y;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			cell = map->content[row * map->width + col];
			pixels_x = col * GRID;
			pixels_y = row * GRID;
			if (cell == '1')
				mlx_put_image_to_window(screen->display, screen->window, water, pixels_x, pixels_y);
			else
				mlx_put_image_to_window(screen->display, screen->window, grass, pixels_x, pixels_y);
			
			if(cell == 'C')
				mlx_put_image_to_window(screen->display, screen->window, wool, pixels_x, pixels_y);
			if(cell == 'E')
				mlx_put_image_to_window(screen->display, screen->window, hole, pixels_x, pixels_y);
			if (cell == 'P')
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

int	main(void)
{
	t_xvar* display;
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

	map = read_map("maps/test_map.ber");
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

	fill_map(&screen, map, &character, background.background, water, wool, hole);
	mlx_key_hook(window, &key_delegator, &character);
	mlx_loop(display);
	mlx_destroy_display(display);

	return(0);
}
