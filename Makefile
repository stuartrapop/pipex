NAME = pipex

SRCS_PATH_GNL = ./gnl
SRCS_PATH_MAIN = ./main

OBJS_PATH = ./

SRCS_NAME_MAIN = pipex.c \
			ft_split.c \
			ft_strncmp.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			helpers.c \
			initialization.c \
			execution.c \
			parse.c \

SRCS_NAME_GNL = gnl.c \
			gnl_utils.c


SRCS = $(addprefix $(SRCS_PATH_MAIN)/,$(SRCS_NAME_MAIN))
SRCS += $(addprefix $(SRCS_PATH_GNL)/,$(SRCS_NAME_GNL))


HEADER_DIR = ./headers

FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR)

CC = GCC $(FLAG)

OBJS = ${SRCS:.c=.o}

%.o:%.c
	$(CC) -o $@ -c $<

${NAME} : ${OBJS}
	$(CC)    $(OBJS) -o ${NAME}

all : ${NAME}
	@echo "$(COLOUR_RED)Make ${NAME} completed$(COLOUR_END)"

clean :
	rm -f ${OBJS} $(OBJS_BONUS)
	@echo "$(COLOUR_GREEN)Make Clean Executed$(COLOUR_END)"

fclean : clean
	rm -f ${NAME}
	rm -f "heredoc.txt"
	@echo "$(COLOUR_RED)Executable ${NAME} removed $(COLOUR_END)"

re : fclean all

bonus : fclean all
	@echo "$(COLOUR_RED)Make Bonus$(COLOUR_END)"

.PHONY : all clean fclean re

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m