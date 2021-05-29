#include "server.h"
#include <stdio.h>

t_server g_server;

void	write_pid(pid_t pid)
{
	char r;

	if (pid >= 10)
		write_pid(pid / 10);
	r = (pid % 10) + '0';
	write(1, &r, 1);
}

void	len_msg(int sig)
{
	int num;

	num = sig == 30 ? 0 : 1;
	/*g_server.len_msg |= num << g_server.i;*/
	printf("%d\n", num);
}

void	get_len_msg(void)
{
	g_server.i = 0;
	if (!g_server.len_done)
	{
		while (g_server.i < 32)
		{
			signal(SIGUSR1, len_msg);
			signal(SIGUSR2, len_msg);
			g_server.i++;
		}
		g_server.len_done = 1;
	}
}

#include <stdio.h>

int main()
{
	pid_t pid;

	pid = getpid();
	write_pid(pid);
	write(1, "\n", 1);
	get_len_msg();
	while (1)
	{
		pause();
	}
}
