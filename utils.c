#include "get_next_line.h"
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t			index;
	unsigned char	c1;
	unsigned char	c2;

	if (size == 0)
		return (0);
	index = 0;
	while (s1[index] == s2[index] && index < size
		&& s1[index] != '\0' && s2[index] != '\0')
		index++;
	if (index == size && index != 0)
	{
		c1 = s1[index - 1];
		c2 = s2[index - 1];
		return ((int)(c1 - c2));
	}
	c1 = s1[index];
	c2 = s2[index];
	return ((int)(c1 - c2));
}

char	*ft_strchr(const char *string, int c)
{
	unsigned int	index;
	char			convert_c;

	convert_c = (char) c;
	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] == convert_c)
			return ((char *) &string[index]);
		index++;
	}
	if (string[index] == convert_c)
		return ((char *) &string[index]);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t	size;

	size = write(fd, s, len(s));
	(void) size;
}

static void	ft_make_char_number_fd(int n, char *number, int digit, char signal)
{
	digit += signal;
	number[digit] = '\0';
	digit--;
	while (digit >= 0)
	{
		number[digit] = n % 10 + '0';
		n = n / 10;
		digit--;
	}
	if (signal == 1)
		number[digit + 1] = '-';
}

void	ft_putnbr_fd(int n, int fd)
{
	char	number[12];
	char	signal;
	int		digit;
	int		numerator;

	signal = 0;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		signal = 1;
	}
	digit = 1;
	numerator = n;
	while (numerator > 9)
	{
		numerator = numerator / 10;
		digit++;
	}
	ft_make_char_number_fd(n, number, digit, signal);
	ft_putstr_fd(number, fd);
}
