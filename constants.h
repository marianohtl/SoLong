/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:30:33 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:36:23 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H
# define GRID 50
# define MAX_WIDTH 38
# define MAX_HEIGHT 19
# define GAME_TITLE "Deletinho"
# define SAND "./images/xpm/sand.xpm"
# define WATER "./images/xpm/water.xpm"
# define WOOL "./images/xpm/wool.xpm"
# define HOLE "./images/xpm/hole.xpm"
# define R_CAT "./images/xpm/right_cat.xpm"
# define E_CAT "./images/xpm/right_cat.xpm"
# define L_CAT "./images/xpm/left_cat.xpm"

typedef int	(*t_key_function)(void *param);

#endif
