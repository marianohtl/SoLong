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
	char *buffer;
	int pixel_bits;
	int line_bytes;
	int endian;
	int width;
	int height;

	display = mlx_init();
	window = mlx_new_window(display, 400 , 400, "Nezuko Chaaan");

	screen.display = display;
	screen.window = window;
	image = mlx_new_image(display, 200 , 200);
	buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	buffer[16100] = 255;
	buffer[16101] = 255;
	buffer[16102] = 255;
	buffer[16104] = 255;
	buffer[16105] = 255;
	buffer[16106] = 255;
	buffer[16108] = 255;
	buffer[16109] = 255;
	buffer[16110] = 255;

	image = mlx_xpm_file_to_image(display,"./images/xpm/nezukoChan.xpm", &width, &height);

	mlx_put_image_to_window(display, window, image, 0,0);
	mlx_key_hook(window, destroy_display, &screen);
	mlx_loop(display);
	mlx_destroy_display(display);

	return(0);
}