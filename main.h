/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:51:41 by mfunyu            #+#    #+#             */
/*   Updated: 2021/01/08 12:24:34 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef STDOUT
#  define STDOUT 0
# endif

# define TERMINATE NULL

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
// int		ft_strcmp(const char *s1, const char *s2);
// char	*ft_strdup(const char *s2);
// ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);
// ssize_t	ft_read(int fildes, void *buf, size_t nbyte);

#endif
