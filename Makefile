# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:57:28 by monoue            #+#    #+#              #
#    Updated: 2021/01/14 14:26:29 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libasm.a

NA		= nasm
NFLAGS	= -g -Fdwarf -f macho64

SRCS	= ft_strlen.s \
		  ft_strcpy.s \
		  ft_strcmp.s \
		  ft_write.s \
		  ft_read.s \
		  ft_strdup.s \
		  ft_list_size_bonus.s \
		  ft_list_push_front_bonus.s

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

strcmp: ft_strcmp.o
	$(RM) ft_strcmp.o strcmp
	nasm -g -f macho64 ft_strcmp.s
	ld ft_strcmp.o -lSystem -o strcmp

clean:
	$(RM) $(OBJS) libasm

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: re
	./libasm

.PHONY: all clean fclean re
