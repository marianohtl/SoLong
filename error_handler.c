#include "structs.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	map_error(t_maps *map, int limit, char *message, \
	void (*free_map)(t_maps *, int))
{
	free_map(map, limit);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	exit(1);
}

void	quit_program(char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	exit(1);
}

void	system_error(char *message)
{
	perror(message);
	exit(1);
}
