# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jconcent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 22:11:30 by jconcent          #+#    #+#              #
#    Updated: 2020/11/14 22:40:52 by jconcent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = src/main.c\
	  src/util.c\
	  src/graphics.c
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -I include/ -I libft/includes/ -I minilibx/ -I /usr/include/X11 -I /usr/include/X11/extensions -c $< -o $@

include $(wildcard $(DEP))

minilibx/libmlx_Linux.a:
	make -C minilibx/

libft/libft.a:
	make -C libft/

$(NAME): $(OBJ) libft/libft.a minilibx/libmlx_Linux.a
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) libft/libft.a minilibx/libmlx_Linux.a -lX11 -lXext -lm

clean:
	rm -f $(OBJ) $(DEP)
	make -C libft/ clean
	make -C minilibx/ clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a
	rm -f minilibx/libmlx_Linux.a

re: fclean all

.PHONY: all clean fclean re
