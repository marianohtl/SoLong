/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:34:13 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:34:14 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
# include "structs.h"

void	free_map(t_maps *map, int limit);
void	clean_map_visit(t_maps *map);
t_maps	*read_map(const char *file);
void	fill_map(t_maps *map, t_characters *character);

#endif
