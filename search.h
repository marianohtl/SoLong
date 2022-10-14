/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:07 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:35:08 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_H
# define SEARCH_H
# include "structs.h"

t_nodes	*new_node(int x, int y, char element);
t_nodes	*search(t_maps *map, t_nodes *start, t_nodes *target);

#endif
