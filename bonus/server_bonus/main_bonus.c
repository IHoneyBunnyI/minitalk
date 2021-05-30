#include "server_bonus.h"
#include <stdio.h>

t_server	g_server;

void	write_pid(pid_t pid)
{
	char	r;

	if (pid >= 10)
		write_pid(pid / 10);
	r = (pid % 10) + '0';
	write(1, &r, 1);
}

void	len_msg(int sig)
{
	int	bit;
	int	i;

	i = -1;
	if (sig == 30)
		bit = 0;
	else
		bit = 1;
	g_server.len_msg |= bit << g_server.i++;
	if (g_server.i == 32)
	{
		g_server.i = 0;
		g_server.msg = malloc(sizeof(char) * (g_server.len_msg + 1));
		g_server.msg[g_server.len_msg] = 0;
		while (++i < g_server.len_msg)
			g_server.msg[i] = 0;
		g_server.i_char = 0;
		signal(SIGUSR1, msg);
		signal(SIGUSR2, msg);
	}
}

void	msg(int sig)
{
	int	bit;

	if (sig == 30)
		bit = 0;
	else
		bit = 1;
	g_server.msg[g_server.i_char] |= bit << g_server.i++;
	if (g_server.i == 8)
	{
		g_server.i = 0;
		g_server.i_char++;
		if (g_server.i_char == g_server.len_msg)
		{
			g_server.i_char = 0;
			g_server.i = 0;
			write(1, g_server.msg, g_server.len_msg);
			write(1, "\n", 1);
			g_server.len_msg = 0;
			free(g_server.msg);
			signal(SIGUSR1, len_msg);
			signal(SIGUSR2, len_msg);
		}
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	write_pid(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, len_msg);
	signal(SIGUSR2, len_msg);
	while (1)
		pause();
}
