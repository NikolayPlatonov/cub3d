# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flegg <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 16:02:20 by flegg             #+#    #+#              #
#    Updated: 2021/02/06 16:02:28 by flegg            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCDIR	=	src/
OBJDIR	=	obj/
INCDIR	=	include/

CC		=	gcc
OFLAGS	=	-Wall -Werror -Wextra -Imlx -I $(INCDIR)
BFLAGS	=	-framework OpenGL -framework AppKit

SRCS	=	main.c \
			main_utils.c \
			parser/read_map_list.c \
			parser/read_map_params.c \
			parser/parse_params_1.c \
			parser/parse_params_2.c \
			parser/map_close_check.c \
			parser/map_close_check_v2.c \
			parser/map_close_check_utils.c \
			parser/locate_sprites.c \
			parser/locate_player.c \
			parser/check_path.c \
			parser/parser.c \
			game/player_move.c \
			game/player_rotate.c \
			game/sprites.c \
			game/sprites_utils.c \
			game/hooks.c \
			game/textures.c \
			game/draw.c \
			game/draw_walls.c \
			game/draw_walls_utils.c \
			game/screenshot.c \
			init.c \
			free.c \
			mem_manager.c \
			mem_manager_utils.c \
			emsg.c

SRCFULL	=	$(addprefix $(SRCDIR), $(SRCS))
OBJS	=	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCFULL))

.PHONY: all
all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p "$(OBJDIR)parser/"
	mkdir -p "$(OBJDIR)game/"

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(OFLAGS) -g -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C mlx
	$(CC) $(BFLAGS) -g $(OBJS) libft/libft.a mlx/libmlx.a -o $(NAME)

libclean:
	$(MAKE) clean -C libft

libfclean:
	$(MAKE) fclean -C libft

mlxclean:
	$(MAKE) clean -C mlx

clean:
	rm -rf $(OBJS) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

ffclean: libfclean mlxclean fclean

re: fclean all
