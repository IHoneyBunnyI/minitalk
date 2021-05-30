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
	rm -rf $(OBJS_SERVER_BONUS)
	rm -rf $(OBJS_CLIENT_BONUS)

fclean: clean
	rm -rf $(SERVER)
	rm -rf $(CLIENT)
	rm -rf $(SERVER_BONUS)
	rm -rf $(CLIENT_BONUS)

re: fclean all

FILES_SERVER_BONUS = main_bonus.c\

FILES_CLIENT_BONUS = main_bonus.c\
	       util_bonus.c\

SRC_SERVER_BONUS = $(addprefix bonus/server_bonus/, $(FILES_SERVER_BONUS))
SRC_CLIENT_BONUS = $(addprefix bonus/client_bonus/, $(FILES_CLIENT_BONUS))

OBJS_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

SERVER_BONUS = bonus/server_bonus/server
CLIENT_BONUS = bonus/client_bonus/client


bonus : $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS) : $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) -o $(SERVER_BONUS) $(OBJS_SERVER_BONUS)

$(CLIENT_BONUS) : $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o $(CLIENT_BONUS) $(OBJS_CLIENT_BONUS)
