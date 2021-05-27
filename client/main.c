#include "client.h"

int	number(char *s)
{
	int result;

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
	int i;
	char bit;

	i = 0;
	while (i < 8)
	{
		bit = byte >> i & 1;
		if (bit == 0)
		{
			printf("0\n");
			kill(number(pid), SIGUSR1);
		}
		if (bit == 1)
		{
			printf("1\n");
			kill(number(pid), SIGUSR2);
		}
		i++;
	}
	printf("--\n");
}

int main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac == 3 && only_numbers(av[1]))
	{
		while (av[2][i])
		{
			send_byte(av[2][i], av[1]);
			i++;
		}
	}
	else
		write(1, "Error\n", 6);
}
