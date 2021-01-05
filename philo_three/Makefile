NAME = philo_three
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = utils.c \
	   initing.c \
	   main.c \
	   parsing.c \
	   utils2.c  \
	   philo_funcs.c \
	   filling_init_data.c \
	   killing.c \
	   utils3.c \

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
