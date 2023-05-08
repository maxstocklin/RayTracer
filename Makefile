#Compilation setting

NAME	=	minirt
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-g -fsanitize=address

##-----VARIABLES-----##
COLOR			= \033
WHITE			= $(COLOR)[97m
CYAN			= $(COLOR)[96m
GREEN			= $(COLOR)[32m
BLUE			= $(COLOR)[34m
RED 			= $(COLOR)[31m
YELLOW			= $(COLOR)[33m
MAGENTA 		= $(COLOR)[35m
BOLD			= $(COLOR)[1m
RESET			= $(COLOR)[0m
RESET_BOLD		= $(COLOR)[21m

#Libraries
RT_HELPERS = ./rt_helpers

#Sources
DIR_SRC	=	./srcs
SRCS_NAME	=	main.c \
				init.c \
				check.c \
				split_spaces.c \
				errors.c \
				utils1.c \
				utils2.c \
				utils3.c \
				assignment1.c \
				assignment2.c \
				assignment3.c \
				assignment4.c \
				get_next_line.c \
				get_next_line_utils.c \
				free.c \
				printed.c \
				printed2.c \
				plane_fns.c \
				hooks.c \
				hooks2.c \
				make_rays.c \
				sphere_fns.c \
				sphere_fns2.c \
				cylinder_fns.c \
				cone_fns.c \
				get_intersect.c \
				get_intersect2.c \
				apply_light.c \
				apply_light2.c \
				cylinder_utils.c \
				closest_obj.c \
				closest_obj2.c \
				discs_fns.c \
				bump.c \
				photon_map.c \
				rotate.c

SRCS = 		$(addprefix $(DIR_SRC)/,$(SRCS_NAME))

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

all : ${NAME} asciiart

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


asciiart:
	@echo "$(RED)                                                                            										"
	@echo "                                                                                     									"
	@echo "                                                                                     									"
	@echo "		███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗   						"
	@echo "		████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝   						"
	@echo "		██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║   						"
	@echo "		██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║   						"
	@echo "		██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║   						"
	@echo "		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝   						"
	@echo "$(BLUE)                                                                                       							"
	@echo "		██████╗ ██╗   ██╗    ███████╗██████╗  █████╗ ██████╗  ██████╗ ██████╗  ██████╗ ██████╗   						"
	@echo "		██╔══██╗╚██╗ ██╔╝    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔═══██╗██╔══██╗   						"
	@echo "		██████╔╝ ╚████╔╝     ███████╗██████╔╝███████║██████╔╝██║   ██║██████╔╝██║   ██║██████╔╝   						"
	@echo "		██╔══██╗  ╚██╔╝      ╚════██║██╔══██╗██╔══██║██╔═══╝ ██║   ██║██╔═══╝ ██║   ██║██╔══██╗   						"
	@echo "		██████╔╝   ██║       ███████║██║  ██║██║  ██║██║     ╚██████╔╝██║     ╚██████╔╝██║  ██║   						"
	@echo "		╚═════╝    ╚═╝       ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ ╚═╝      ╚═════╝ ╚═╝  ╚═╝   						"
	@echo "$(GREEN)                                                                                       							"
	@echo "		   ██╗       ███╗   ███╗███████╗████████╗ ██████╗  ██████╗██╗  ██╗██╗     ██╗   						"
	@echo "		   ██║       ████╗ ████║██╔════╝╚══██╔══╝██╔═══██╗██╔════╝██║ ██╔╝██║     ██║   						"
	@echo "		████████╗    ██╔████╔██║███████╗   ██║   ██║   ██║██║     █████╔╝ ██║     ██║   						"
	@echo "		██╔═██╔═╝    ██║╚██╔╝██║╚════██║   ██║   ██║   ██║██║     ██╔═██╗ ██║     ██║   						"
	@echo "		██████║      ██║ ╚═╝ ██║███████║   ██║   ╚██████╔╝╚██████╗██║  ██╗███████╗██║   						"
	@echo "		╚═════╝      ╚═╝     ╚═╝╚══════╝   ╚═╝    ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝   						"
	@echo "   						"

