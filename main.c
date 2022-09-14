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

int main()
{
	void* display;
	void* window;
	screens screen;
	void*  image;
	void*  image2;
	int width;
	int height;
	char *buffer;
	int pixel_bits;
	int line_bytes;
	int endian;
	int count;

	display = mlx_init();
	window = mlx_new_window(display, 400 , 400, "Nezuko Chaaan");

	screen.display = display;
	screen.window = window;

	image = mlx_xpm_file_to_image(display,"./images/xpm/nezukoChan.xpm", &width, &height);

	image2 = mlx_xpm_file_to_image(display,"./images/xpm/left_cat.xpm", &width, &height);

	buffer = mlx_get_data_addr(image2, &pixel_bits, &line_bytes, &endian);
	count = 0;
	while (count < 23104)
	{
		if ((buffer[count + 0] == -1) && (buffer[count + 1] == -1) && (buffer[count + 2] == -1))
			{
				buffer[count + 3] = -1;
			}

		count+= 4;
	}

	mlx_put_image_to_window(display, window, image, 0,0);
	mlx_put_image_to_window(display, window, image2, 100,100);
	mlx_key_hook(window, destroy_display, &screen);
	mlx_loop(display);
	mlx_destroy_display(display);

	return(0);
}
