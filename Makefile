#Compilation setting

NAME	=	minirt
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address

#Libraries
RT_HELPERS = ./rt_helpers

#Sources
DIR_SRC=./srcs
SRCS	=	${DIR_SRC}/main.c \
			${DIR_SRC}/init.c \
			${DIR_SRC}/check.c \
			${DIR_SRC}/split_spaces.c \
			${DIR_SRC}/errors.c \
			${DIR_SRC}/utils.c \
			${DIR_SRC}/assignment.c \
			${DIR_SRC}/get_next_line.c \
			${DIR_SRC}/get_next_line_utils.c \
			${DIR_SRC}/free.c \
			${DIR_SRC}/printed.c \
			${DIR_SRC}/hooks.c

DIR_OBJ=./objs
OBJS=${addprefix ${DIR_OBJ}/, ${notdir ${SRCS:.c=.o}}}

#Find the os
UNAME_S := $(shell uname -s)

#Linux
#$(CC)
#$(OBJS) -L${DIR_LIB_MLX}/ -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
ifeq ($(UNAME_S),Linux)
		DIR_LIB_MLX= ./mlx-linux
		DIR_LIB_SYS= ./usr/lib
		OFLAGS=-L${DIR_LIB_MLX} -lmlx  -I${DIR_LIB_MLX} -lXext -lX11 -lm -lz -L${RT_HELPERS} -lhelpers
endif
#L/usr/lib

#Apple
#$(CC) $(OBJS)		 -L${DIR_LIB_MLX}/ -Imlx -lmlx -o $(NAME)
#$(CC) $(OBJS) -L${DIR_LIB_M	LX}/ -Imlx-apple -lmlx -o $(NAME)

ifeq ($(UNAME_S),Darwin)
		DIR_LIB_MLX=mlx
		OFLAGS=-L${DIR_LIB_MLX} -lmlx -L${RT_HELPERS} -lhelpers -framework OpenGL -framework AppKit
endif

vpath %.c ${DIR_SRC}
RM=rm -f

all : ${NAME}

$(NAME):			 $(OBJS)
		#make -C ${DIR_LIB_MLX}
		make -C ${RT_HELPERS}
		$(CC) $(OBJS) -L${DIR_LIB_MLX} ${OFLAGS} -o $(NAME)

${DIR_OBJ}/%.o : %.c | ${DIR_OBJ}
		$(CC) ${CFLAGS} -I${DIR_LIB_MLX} -O3 -c $< -o $@

${DIR_OBJ} :
		@mkdir -p ${DIR_OBJ}

clean:
		#make clean -C ${DIR_LIB_MLX}
		make clean -C ${RT_HELPERS}
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all
		#make re -C ${DIR_LIB_MLX}

.PHONY:		all clean fclean re

norm:
		norminette ${SRCS}