# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/05 21:20:46 by mfunyu            #+#    #+#              #
#    Updated: 2021/08/07 16:05:09 by mfunyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol

SRCFILES:= color.c \
		exit.c \
		hooks.c \
		julia.c \
		mandelbrot.c \
		params.c \
		puts.c \
		utils.c \
		zoom.c
SRCS	:= $(SRCFILES) main.c
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

# for leak check
ifeq ($(shell uname), Darwin)
	SRCS_LEAK := $(SRCFILES) main_leak_check.c
	CFLAGS_LEAK:= $(CFLAGS)
else if ($(shell uname), Linux)
	SRCS_LEAK := $(SRCFILES) main.c
	CFLAGS_LEAK:= $(CFLAGS) -g -fsanitize=address
endif
SRCS_LEAK := $(addprefix srcs/,$(SRCS_LEAK))
OBJS_LEAK	:= $(SRCS_LEAK:.c=.o)


.PHONY	: all clean fclean re

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

leak	: fclean $(LIBMLX) $(OBJS_LEAK)
	make -C $(LIBFT)
	make -C $(LIBMLX)
	$(CC) $(CFLAGS_LEAK) -o $(NAME) $(OBJS_LEAK) $(LIBS)

$(OBJS_LEAK) : srcs/%.o : srcs/%.c
	$(CC) $(CFLAGS_LEAK) -c -o $@ $<

# compile .d files
# %.o : %.c
# 	$(CC) $(CFLAGS) -c -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $<

clean	:
	make clean -C $(LIBFT)
ifeq ($(shell echo ${LIBMLX}), $(shell ls | grep ${LIBMLX})))
	make clean -C $(LIBMLX)
endif
	$(RM) $(OBJS) $(OBJS_LEAK) $(DEPS)

fclean	: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re		: fclean all
