# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:57:28 by monoue            #+#    #+#              #
#    Updated: 2021/01/08 12:03:32 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libasm.a

NA		= nasm
NFLAGS	= -g -f macho64

SRCS	= ft_strlen.s \
		  ft_strcpy.s

OBJS	= $(SRCS:%.s=%.o)

UNAME	= udemy
UDEMY	= udemy.s
UOBJS	= $(UDEMY:%.s=%.o)

all: $(NAME)

%.o:%.s
	$(NA) $(NFLAGS) $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)
	gcc -g main.c libasm.a -o libasm

udemy: $(UOBJS)
	$(RM) $(UOBJS) $(UNAME)
	nasm -g -f macho64 $(UDEMY)
	ld udemy.o -lSystem -o $(UNAME)

clean:
	$(RM) $(OBJS) libasm

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
