NAME = philo_one
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = utils.c \
	   initing.c \
	   main.c \
	   parsing.c \

OBJS = $(SRCS:.c=.o)
RM = rm -rf
all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re:	fclean $(NAME)
.PHONY: all clean fclean re