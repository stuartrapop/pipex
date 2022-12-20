NAME = pipex

SRCS_PATH =./

OBJS_PATH = ./

SRCS_NAME = pipex.c \
			ft_split.c \
			ft_strncmp.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			helpers.c \
			initialization.c \
			execution.c \
			parse.c \
			gnl.c \
			gnl_utils.c


SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))


HEADER_DIR = ./

FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR)

CC = GCC $(FLAG)

OBJS = ${SRCS:.c=.o}

%.o:%.c
	$(CC) -o $@ -c $<

${NAME} : ${OBJS}
	$(CC)    $(OBJS) -o ${NAME}

all : ${NAME}

clean :
	rm -f ${OBJS} $(OBJS_BONUS)

fclean : clean
	rm -f ${NAME}

re : fclean all

bonus : fclean all

.PHONY : all clean fclean re
