#include "get_next_line.h"
#include <unistd.h>

static int	ft_char_diff(const char *s1, const char *s2, size_t index)
{
	return ((int)((unsigned char)s1[index] - (unsigned char)s2[index]));
}

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	index;

	if (size == 0)
		return (0);
	index = 0;
	while (s1[index] == s2[index] && index < size
		&& s1[index] != '\0' && s2[index] != '\0')
		index++;
	if (index == size && index != 0)
		return (ft_char_diff(s1, s2, index - 1));
	return (ft_char_diff(s1, s2, index));
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
	write (fd, s, len(s));
}

static int	ft_get_digit_fd(int numerator)
{
	int	digit;

	digit = 1;
	while (numerator > 9)
	{
		numerator = numerator / 10;
		digit++;
	}
	return (digit);
}

static void	ft_make_char_number_fd(int n, char *number, int digit, char signal)
{
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
	digit = ft_get_digit_fd(n) + signal;
	ft_make_char_number_fd(n, number, digit, signal);
	ft_putstr_fd(number, fd);
}
