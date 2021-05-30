#include "client.h"

int	number(char *s)
{
	int	result;

	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		result = (result * 10) + *s - '0';
		s++;
	}
	return (result);
}

void	send_byte(char byte, char *pid)
{
	int		i;
	char	bit;

	i = 0;
	while (i < 8)
	{
		bit = (byte >> i) & 1;
		if (bit == 0)
			kill(number(pid), SIGUSR1);
		if (bit == 1)
			kill(number(pid), SIGUSR2);
		usleep(100);
		i++;
	}
}

void	send_len_msg(int len_msg, char *pid)
{
	int		i;
	char	bit;

	i = 0;
	while (i < 32)
	{
		bit = (len_msg >> i) & 1;
		if (bit == 0)
			kill(number(pid), SIGUSR1);
		if (bit == 1)
			kill(number(pid), SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	len_msg;

	i = 0;
	len_msg = 0;
	if (ac == 3 && only_numbers(av[1]))
	{
		len_msg = ft_strlen(av[2]);
		send_len_msg(len_msg, av[1]);
		while (av[2][i])
		{
			send_byte(av[2][i], av[1]);
			i++;
		}
	}
	else
		write(1, "Error\n", 6);
}
