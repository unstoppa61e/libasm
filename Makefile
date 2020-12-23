# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:57:28 by monoue            #+#    #+#              #
#    Updated: 2020/12/23 12:32:20 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libasm.a

NA		= nasm
NFLAGS	= -f macho64

SRCS	= ft_strlen.s \
		  ft_strcpy.s

OBJS	= $(SRCS:%.s=%.o)

all: $(NAME)

%.o:%.s
	$(NA) $(NFLAGS) $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
