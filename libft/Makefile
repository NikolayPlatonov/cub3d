# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flegg <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 18:31:27 by flegg             #+#    #+#              #
#    Updated: 2020/11/18 18:32:05 by flegg            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra

SRCDIR	=	src/
OBJDIR	=	obj/

SRCS	=	ft_strmapi.c \
			ft_itoa.c \
		 	ft_split.c \
			ft_strtrim.c \
			ft_strjoin.c \
			ft_substr.c \
			ft_putnbr_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putchar_fd.c \
			ft_memset.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memccpy.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstmap.c \
			ft_lstiter.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstadd_back.c \
			ft_lstlast.c \
			ft_lstsize.c \
			ft_lstadd_front.c \
			ft_lstnew.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_strchrpos.c
			

SRCFULL	=	$(addprefix $(SRCDIR), $(SRCS))
OBJS	=	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCFULL))

.PHONY: all
all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS) $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
