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

int main(int ac, char **av)
{
	kill(number(av[1]), SIGUSR1);
}
