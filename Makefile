NAME	:= fractol
SRCS	:= $(wildcard ./srcs/*.c)
OBJS	:= $(SRCS:.c=.o)
DEPS	:= $(SRCS:.c=.d)
LIBFT	:= libft
LIBMLX	:= minilibx-linux
INCLUDES:= -Iinclude -I$(LIBFT) -I$(LIBMLX) -I/usr/X11/include
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror $(INCLUDES)
LIBS	:= -L$(LIBFT) -lft \
			-L$(LIBMLX) -lmlx_Darwin \
			-L/usr/X11/include/../lib -lXext -lX11


all		: $(NAME)

-include $(DEPS)

$(NAME)	: $(LIBMLX) $(OBJS)
# $(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBMLX)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(LIBMLX):
ifneq ($(shell echo ${LIBMLX}), $(shell ls | grep ${LIBMLX})))
	git clone https://github.com/42Paris/minilibx-linux.git
endif


%.o : %.c
	$(CC) $(CFLAGS) -c -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $<

clean	:
# $(MAKE) clean -C $(LIBFT)
ifeq ($(shell echo ${LIBMLX}), $(shell ls | grep ${LIBMLX})))
	$(MAKE) clean -C $(LIBMLX)
endif
	$(RM) $(OBJS) $(DEPS)

fclean	: clean
# $(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME) libmlx.a libmlx_Darwin.a

re		: fclean all

.PHONY	: all clean fclean re