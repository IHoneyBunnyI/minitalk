#include "client.h"

int	only_numbers(char *string)
{
	int i;

	i = 0;
	while (i[string])
	{
		if (i[string] < '0' || i[string] > '9')
			return (0);
		i++;
	}
	return (1);
}
