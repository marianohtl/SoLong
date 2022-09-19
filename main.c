#include"mlx.h"
#include"mlx_int.h"
#include"X11/keysymdef.h"

typedef struct screens
{
	void *window;
	t_xvar *display;
} screens;

int destroy_display(int key_code, void *param)
{
	screens * data;
	data = param;
	if(key_code == XK_Q || key_code == XK_q || key_code == XK_Escape)
	{
		mlx_destroy_window(data->display, data->window);
		mlx_loop_end(data->display);
	}
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
		if (buffer_foreground[pixel] == 0xFF000000)
			buffer_foreground[pixel] = buffer_background[row * background->width + col + \
				pixel % foreground->width + \
				(pixel / foreground->width) * background->width];
		pixel++;
	}
}

int	main(void)
{
	t_xvar* display;
	void* window;
	screens screen;
	t_img*  background;
	t_img*  character;
	int	height;
	int	width;
	int	start_row;
	int	start_col;

	display = mlx_init();
	window = mlx_new_window(display, 400 , 400, "Nezuko Chaaan");
	screen.display = display;
	screen.window = window;

	background = mlx_xpm_file_to_image(display,"./images/xpm/nezukoChan.xpm", &width, &height);
	character = mlx_xpm_file_to_image(display,"./images/xpm/left_cat.xpm", &width, &height);

	start_row = 200;
	start_col = 150;
	merge_image(background, character, start_row, start_col);

	mlx_put_image_to_window(display, window, background, 0,0);
	mlx_put_image_to_window(display, window, character, start_col, start_row);

	mlx_key_hook(window, destroy_display, &screen);
	mlx_loop(display);

	mlx_destroy_display(display);
	return(0);
}
