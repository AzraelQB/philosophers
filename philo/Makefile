NAME = 	philo
HEADER = philo.h
FILES = philo.c \
			init_structs.c \
			philo_life.c \
			ft_utils.c
OBJDIR		= objs/
OBJS		= $(FILES_O:.c=.o)
FILES_O		= $(addprefix objs/, $(FILES))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

.PHONY: all clean fclean bonus

objs/%.o : %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir objs/

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re: fclean all