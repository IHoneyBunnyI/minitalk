#include "server.h"
#include <stdio.h>

void	write_pid(pid_t pid)
{
	char r;

	if (pid >= 10)
		write_pid(pid / 10);
	r = (pid % 10) + '0';
	write(1, &r, 1);
}

void	f(int pid)
{
	printf("0\n");
}

void	f2(int pid)
{
	printf("1\n");
}

int main()
{
	pid_t pid;

	pid = getpid();
	write_pid(pid);
	write(1, "\n", 1);
	signal(SIGUSR2, f2);
	signal(SIGUSR1, f);
	while (1)
	{
		pause();
	}
}
