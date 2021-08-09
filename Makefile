# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/05 21:20:46 by mfunyu            #+#    #+#              #
#    Updated: 2021/08/09 21:12:30 by mfunyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol

SRCS	:= main.c \
		color.c \
		exit.c \
		hooks.c \
		julia.c \
		mandelbrot.c \
		params.c \
		puts.c \
		utils.c \
		zoom.c
SRCS	:= $(addprefix srcs/,$(SRCS))
OBJS	:= $(SRCS:.c=.o)

#DEPS	:= $(SRCS:.c=.d)

LIBFT	:= libft
LIBMLX	:= minilibx-linux
LIBX_INC:= $(shell ./configure)
LIBS	:= -L$(LIBFT) -lft \
			-L$(LIBMLX) -lmlx_$(shell uname) \
			-L$(LIBX_INC)/../lib -lXext -lX11 \
			-lm

INCLUDES:= -Iinclude -I$(LIBFT) -I$(LIBMLX) -I$(LIBX_INC)
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror $(INCLUDES)
DSTRCTR	:= ./tests/destructor.c

.PHONY	: all clean fclean re

#-----------------------------------

# -include $(DEPS)

all		: $(NAME)

$(NAME)	: $(LIBMLX) $(OBJS)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(LIBMLX):
ifneq (${LIBMLX}, $(shell ls | grep ${LIBMLX})))
	git clone https://github.com/42Paris/minilibx-linux.git
endif

Darwin_leak	: $(LIBMLX) $(OBJS)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) $(DSTRCTR) -o $(NAME) $(LIBS)

Linux_leak	: $(LIBMLX) $(OBJS)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME) $(LIBS)

leak	: $(shell uname)_leak

# compile .d files
# %.o : %.c
# 	$(CC) $(CFLAGS) -c -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $<

clean	:
	make clean -C $(LIBFT)
	- make clean -C $(LIBMLX)
	$(RM) $(OBJS) $(DEPS)

fclean	: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re		: fclean all
