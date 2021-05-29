#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_server
{
	int i;
	int i_char;
	int	len_msg;
	int len_done;
	int msg_done;
	char *msg;
}	t_server;

extern t_server g_server;

#endif
