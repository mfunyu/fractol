NAME	= fractol
SRCS	= $(wildcard ./srcs/*.c)
OBJS	= $(SRCS:.c=.o)
DEPS	= $(SRCS:.c=.d)

LIBFT	= libft
LIBMLX	= minilibx-linux
LIBX_INC= $(shell ./configure)
INCLUDES= -Iinclude -I$(LIBFT) -I$(LIBMLX) -I$(LIBX_INC)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror $(INCLUDES)

LIBS	= -L$(LIBFT) -lft \
			-L$(LIBMLX) -lmlx_$(shell uname) \
			-L$(LIBX_INC)/../lib -lXext -lX11

.PHONY	: all clean fclean re do_configure

#-----------------------------------

# -include $(DEPS)

all		: $(NAME)

$(NAME)	: $(LIBMLX) $(OBJS)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(LIBMLX):
ifneq ($(shell echo ${LIBMLX}), $(shell ls | grep ${LIBMLX})))
	git clone https://github.com/42Paris/minilibx-linux.git
endif

# compile .d files
# %.o : %.c
# 	$(CC) $(CFLAGS) -c -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $<

clean	:
	make clean -C $(LIBFT)
ifeq ($(shell echo ${LIBMLX}), $(shell ls | grep ${LIBMLX})))
	make clean -C $(LIBMLX)
endif
	$(RM) $(OBJS) $(DEPS)

fclean	: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME) libmlx.a libmlx_Darwin.a

re		: fclean all
