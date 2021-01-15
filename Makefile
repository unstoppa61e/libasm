# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:57:28 by monoue            #+#    #+#              #
#    Updated: 2021/01/15 10:27:00 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libasm.a

CC		= gcc
NA		= nasm
NFLAGS	= -f macho64
EXEC	= libasm

SRCS	= ft_strlen.s \
		  ft_strcpy.s \
		  ft_strcmp.s \
		  ft_write.s \
		  ft_read.s \
		  ft_strdup.s

BONUS	= ft_list_size_bonus.s \
		  ft_list_push_front_bonus.s

OBJS	= $(SRCS:%.s=%.o)
BOBJS	= $(BONUS:%.s=%.o)

all: $(NAME)

%.o:%.s
	$(NA) $(NFLAGS) $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

bonus: $(BOBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME) $(EXEC)

re: fclean all

test: re
	@$(RM) $(EXEC)
	$(CC) main.c $(NAME) -o $(EXEC)
	./$(EXEC)
	@$(RM) linux_read_output linux_write_output ft_read_output ft_write_output

test_bonus: fclean bonus
	@$(RM) $(EXEC)
	$(CC) main_bonus.c $(NAME) -o $(EXEC)
	./$(EXEC)

.PHONY: all clean fclean re test
