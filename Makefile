NAME = op
SERVER = server/server
CLIENT = client/client

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES_SERVER = main.c\

FILES_CLIENT = main.c\
	       util.c\

SRC_SERVER = $(addprefix server/, $(FILES_SERVER))
SRC_CLIENT = $(addprefix client/, $(FILES_CLIENT))

OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER)


clean:
	rm -rf $(OBJS_SERVER)
	rm -rf $(OBJS_CLIENT)

fclean: clean
	rm -rf $(SERVER)
	rm -rf $(CLIENT)

re: fclean all

