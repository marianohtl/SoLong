/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:33:33 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:35:55 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "get_next_line.h"
#include "maps.h"
#include "utils.h"
#include "error_handler.h"
#include "validation.h"
#include "initializers.h"
#include "movement.h"
#include "mlx.h"
#include "mlx_int.h"

int	destroy_display(void *param)
{
	free_resources(param);
	exit(0);
}

int	key_delegator(int key_code, void *param)
{
	static t_key_function	functions[65536];

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
	if (key_code > 65535 || functions[key_code] == NULL)
		return (0);
	return (functions[key_code](param));
}

int	update_window(void *param)
{
	t_characters	*character;

	character = param;
	fill_map(character->map, character);
	return (0);
}

int	main(int argc, char **argv)
{
	t_screens		screen;
	t_characters	character;
	t_maps			*map;

	if (argc != 2)
		quit_program("Invalid number of arguments. " \
			"Program takes only the map file name as parameter.\n");
	if (ft_strncmp(argv[1] + len(argv[1]) - 4, ".ber", 5) != 0)
		quit_program("Map file name must end with '*.ber' extension.\n");
	map = read_map(argv[1]);
	if (map == NULL)
		system_error("Error\nFailed to open map");
	validate_map(map);
	initialize_screen(&screen, map);
	if (screen.display == NULL || screen.window == NULL)
		map_error(map, map->width * map->height + 1, \
			"Failed to create window on display.\n", &free_map);
	initialize_character(&character, map, &screen);
	fill_map(map, &character);
	mlx_key_hook(screen.window, &key_delegator, &character);
	mlx_hook(screen.window, DestroyNotify, 0, &destroy_display, &character);
	mlx_loop_hook(screen.display, &update_window, &character);
	mlx_loop(screen.display);
	return (0);
}
