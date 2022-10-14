/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmariano <tmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:35:24 by tmariano          #+#    #+#             */
/*   Updated: 2022/10/13 22:35:25 by tmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

char	*ft_strchr(const char *string, int c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
void	ft_putnbr_fd(int n, int fd);

#endif
