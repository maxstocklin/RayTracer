NAME = libhelpers.a

SRCS_PATH = ./src

SRCS_NAME = main.c \
			vect_dot.c \
			vect_angle.c \
			vect_length.c \
			rad_deg_conv.c \
			vect_add_sub.c \
			vect_scale.c \
			screen_world.c \
			vect_cross.c \
			vect_util.c \
			point_util.c \
			refract_fns.c \
			color_fns.c	\
			color_fns_2.c


SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))

OBJS = ${SRCS:.c=.o}



HEADER_DIR = ./

FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR)

CC = GCC $(FLAG)

%.o:%.c
	$(CC) -o $@ -c $<

# $(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# ${NAME} : ${OBJS}
# 	$(CC)   $(OBJS) -o ${NAME}

${NAME} : ${OBJS}
	ar rcs $(NAME) $(OBJS)

all : ${NAME}

clean :
	rm -f ${OBJS} $(OBJS_BONUS)
	rm -f ${NAME}
fclean : clean
	rm -f ${NAME}
re : fclean all

.PHONY : all clean fclean re
