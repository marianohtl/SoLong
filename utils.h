#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

char	*ft_strchr(const char *string, int c);
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t size);
void	ft_putnbr_fd(int n, int fd);

#endif
