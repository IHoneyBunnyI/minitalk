#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_server
{
	int		i;
	int		i_char;
	int		len_msg;
	char	*msg;
}	t_server;

extern t_server	g_server;

void	msg(int sig);

#endif
