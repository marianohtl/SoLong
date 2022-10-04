#include"mlx.h"
#include"mlx_int.h"
#include"X11/keysymdef.h"
#define GRID 50

typedef struct screens
{
	void *window;
	t_xvar *display;
} screens;

typedef struct backgrounds
{
	t_img *background;
} backgrounds;

typedef struct characters
{
	screens *screen;
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
	mlx_destroy_window(screen->display, screen->window);
	mlx_loop_end(screen->display);
}

int	move_right(void *param)
{
	characters	*character;

	character = param;	
	character->col += GRID;
	character->current = character->right;
	merge_image(character->background->background, character->current, character->row, character->col);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, 0,0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}
int	move_left(void *param)
{
	characters	*character;

	character = param;	
	character->col -= GRID;
	character->current = character->left;
	merge_image(character->background->background, character->current, character->row, character->col);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, 0,0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}

int	move_up(void *param)
{
	characters	*character;

	character = param;	
	character->row -= GRID;
	merge_image(character->background->background, character->current, character->row, character->col);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, 0,0);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->current, character->col, character->row);
}

int	move_down(void *param)
{
	characters	*character;

	character = param;	
	character->row += GRID;
	merge_image(character->background->background, character->current, character->row, character->col);
	mlx_put_image_to_window(character->screen->display, character->screen->window, character->background->background, 0,0);
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

int	main(void)
{
	t_xvar* display;
	void* window;
	screens screen;
	characters character;
	backgrounds background;
	int	height;
	int	width;
	int	start_row;
	int	start_col;

	start_row = 75;
	start_col = 150;
	display = mlx_init();
	window = mlx_new_window(display, 549 , 543, "Nezuko Chaaan");
	screen.display = display;
	screen.window = window;

	background.background = mlx_xpm_file_to_image(display,"./images/xpm/nezukoChan.xpm", &width, &height);
	character.right = mlx_xpm_file_to_image(display,"./images/xpm/right_cat.xpm", &width, &height);
	character.left = mlx_xpm_file_to_image(display,"./images/xpm/left_cat.xpm", &width, &height);
	character.current = character.right;
	character.background = &background;
	character.col = start_col;
	character.row = start_row;
	character.screen = &screen;

	merge_image(background.background, character.right, start_row, start_col);

	mlx_put_image_to_window(display, window, background.background, 0,0);
	mlx_put_image_to_window(display, window, character.right, start_col, start_row);
	mlx_key_hook(window, &key_delegator, &character);
	mlx_loop(display);

	mlx_destroy_display(display);
	return(0);
}
