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
	int bit;

	bit = sig == 30 ? 0 : 1;
	g_server.len_msg |= bit << g_server.i++;
}

void	get_len_msg(void)
{
	g_server.i = 0;
	while (!g_server.len_done)
	{
		signal(SIGUSR1, len_msg);
		signal(SIGUSR2, len_msg);
		if (g_server.i == 32)
		{
			g_server.len_done = 1;
			g_server.i = 0;
		}
	}
}

void	msg(int sig)
{
	int bit;

	bit = sig == 30 ? 0 : 1;
	g_server.msg[g_server.i_char] |= bit << g_server.i++;
}

void	get_msg()
{
	g_server.i = 0;
	g_server.i_char = 0;
	while (!g_server.msg_done)
	{
		signal(SIGUSR1, msg);
		signal(SIGUSR2, msg);
		if (g_server.i == 8)
		{
			/*printf("char %c\n", g_server.msg[g_server.i_char]);*/
			g_server.i = 0;
			g_server.i_char++;
			if (g_server.i_char == g_server.len_msg)
			{
				g_server.msg_done = 1;
				g_server.i_char = 0;
			}
		}
	}
	write(1, g_server.msg, g_server.len_msg);
	write(1, "\n", 1);
	g_server.len_msg = 0;
}

int main()
{
	pid_t pid;

	pid = getpid();
	write_pid(pid);
	write(1, "\n", 1);
	while (1)
	{
		if (!g_server.msg_done)
			get_len_msg();
		g_server.msg = malloc(sizeof(char) * (g_server.len_msg + 1));
		g_server.msg[g_server.len_msg] = 0;
		if (!g_server.msg_done)
		{
			g_server.len_done = 0;
			get_msg();
		}
		free(g_server.msg);
		/*g_server.msg = 0;*/
		g_server.i = 0;
		g_server.i_char = 0;
		g_server.len_msg = 0;
		g_server.len_done = 0;
		g_server.msg_done = 0;
	}
}
