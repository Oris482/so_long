# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaesjeon <jaesjeon@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 15:37:47 by jaesjeon          #+#    #+#              #
#    Updated: 2022/06/24 14:15:39 by jaemjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS =
MLX_FLAGS = -framework OpenGL -framework AppKit
RM = rm -f

NAME = so_long
LIBFT = libft.a
MLX = libmlx.a
LIBFT_DIR = ./libft
MLX_DIR = ./mlx

SRCS_FILES = so_long.c	\
			 get_next_line.c	\
			 get_next_line_utils.c	\
			 draw_map.c
SRCS_DIR = ./srcs
HEADER_DIR = ./srcs

LIBFT_HEADER = $(LIBFT_DIR)/libft.h
PS_HEADER = 
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT_HEADER) $(PS_HEADER) $(OBJS)
	make bonus -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) .
	make -C $(MLX_DIR)
	cp $(MLX_DIR)/$(MLX) .
	export DYLD_LIBRARY_PATH=$$(pwd);\
	$(CC) $(CFLAGS) -g $(MLX_FLAGS) $(SRCS) -I$(HEADER_DIR) -L. -lft -lmlx -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS)

fclean:
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(LIBFT)
	$(RM) $(MLX)
	$(RM) $(OBJS)
	$(RM) $(NAME)

re: fclean all
