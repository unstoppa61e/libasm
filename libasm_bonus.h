/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 07:25:41 by monoue            #+#    #+#             */
/*   Updated: 2021/01/15 10:25:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBASM_H
# define LIBASM_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

# define ESC		"\033"
# define RED_S		ESC"[31:1m"
# define GREEN_S	ESC"[32:1m"
# define YELLOW_S	ESC"[33:1m"
# define BLUE_S		ESC"[34:1m"
# define PURPLE_S	ESC"[35:1m"
# define CYAN_S		ESC"[36:1m"
# ifndef RESET
#  define RESET		ESC"[m"
# endif

# define OK			1
# define KO			0
# define SUCCESS	0
# define ERROR		-1

// # define BUFFER_SIZE 512 // write command's max writable size at a time
# define BUFFER		512 // write command's max writable size at a time

# define ITOC(num) num + '0' 

typedef enum	e_colors{
	RED_N,
	GREEN_N,
	YELLOW_N,
	BLUE_N,
	PURPLE_N,	
	CYAN_N,

	COLORS_NUM
}				t_colors;

typedef struct	s_list
{
	void 			*data;
	struct s_list 	*next;
}				t_list;

int		ft_list_size(t_list *begin_list);
void	ft_list_push_front(t_list **begin_list, void *data);

#endif
