/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 20:57:50 by mfunyu            #+#    #+#             */
/*   Updated: 2021/01/12 16:06:44 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "u_main.h"

/*
** check_functions:
** 	variadic functions (all very similar)
** 	after third arguments, accpet parameters to pass to the function
** 	using va_list, apply all arguments as a parameter to the function
** 	NULL is used for terminating to read arguments
*/

// void	check_read(FILE *fd, ssize_t (*func)(int, void *, size_t), ...)
// {
// 	va_list	ap;
// 	int		testnbr;
// 	char	*param;
// 	char	*buff;
// 	int		ret;
// 	int		fildes;
// 	int		byte;

// 	testnbr = 0;
// 	va_start(ap, func);
// 	buff = (char *)malloc(40);
// 	while ((param = va_arg(ap, char *)))
// 	{
// 		// open a file
// 		fildes = open(param, O_RDONLY);
// 		byte = va_arg(ap, int);
// 		ret = (*func)(fildes, buff, byte);
// 		buff[byte] = '\0';
// 		// check return values
// 		fprintf(fd, "[read%d]: %d | \"%s\"\n", ++testnbr, ret, buff);
// 		close(fildes);
// 	}
// 	free(buff);
// 	buff = NULL;
// 	va_end(ap);
// }

void	check_write(FILE *fd, ssize_t (*func)(int, const void *, size_t), ...)
{
	va_list	ap;
	char	*param
	ssize_t	ret;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	if (!STDOUT)
		write(fd->_file, "====== write ======\n", 20);
	while ((param = va_arg(ap, char *)))
	{
		// write to each files
		if (!STDOUT)
			write(fd->_file, "[write]: \"", 10);
		else
			write(fd->_file, "\"", 1);
		ret = (*func)(fd->_file, param, strlen(param));
		write(fd->_file, "\"\n", 2);
		// check return values
		fprintf(fd, "[write%d]: %ld\n", ++testnbr, ret);
	}
	va_end(ap);
}

// void	check_strdup(FILE *fd, char *(*func)(const char *), ...)
// {
// 	va_list	ap;
// 	char	*param;
// 	char	*dst;
// 	int		testnbr;

// 	testnbr = 0;
// 	va_start(ap, func);
// 	while ((param = va_arg(ap, char *)))
// 	{
// 		dst = (*func)(param);
// 		fprintf(fd, "[strdup%d] %s | input: %s | ", ++testnbr, dst, param);
// 		// fprintf(fd, "[strdup%d] %s (%p) | input: %s (%p) | ", ++testnbr, dst, dst, param, param);
// 		if (dst != param)
// 			fprintf(fd, "ADRS DIFF (%p)\n", param);
// 		free(dst);
// 		dst = NULL;
// 	}
// 	va_end(ap);
// }

// void	check_strcmp(FILE *fd, int (*func)(const char *, const char *), ...)
// {
// 	va_list	ap;
// 	char	*s1;
// 	char	*s2;
// 	int		testnbr;

// 	testnbr = 0;
// 	va_start(ap, func);
// 	while ((s1 = va_arg(ap, char *)))
// 	{
// 		s2 = va_arg(ap, char *);
// 		fprintf(fd, "[strcmp%d] %d | %s, %s\n", ++testnbr, (*func)(s1, s2), s1, s2);
// 	}
// 	va_end(ap);
// }


void	check_strcpy(FILE *fd, char *(*func)(char *, const char *), ...)
{
	va_list	ap;
	char	*param;
	char	*dst;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	if (!(dst = (char *)calloc(sizeof(char), 30)))
		exit(EXIT_FAILURE);
	while ((param = va_arg(ap, char *)))
	{
		memset(dst, 'a', 20);
		fprintf(fd, "[strcpy%d] src = \"%s\" (%p)\n", ++testnbr, param, param);
		fprintf(fd, "          (before) dst = \"%s\" (%p)\n", dst, dst);
		(*func)(dst, param);
		fprintf(fd, "          (after)  dst = \"%s\" (%p)\n", dst, dst);
	}
	free(dst);
	dst = NULL;
	va_end(ap);
}

void	check_strlen(FILE *fd, size_t (*func)(const char *), ...)
{
	va_list	ap;
	char	*param;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	while ((param = va_arg(ap, char *)))
	{
		fprintf(fd, "[strlen%d] %ld | input: \"%s\"\n", ++testnbr, func(param), param);
	}
	va_end(ap);
}

int		main(int ac, char **av)
{
	FILE	*fd[4];
	char 	*param;
	char	*ft[2];

	if (ac < 2)
		param = "test123";
	else
		param = av[1];

	// open and write into log files
	if ((fd[0] = fopen("actual.log", "w")) == NULL)
		exit(EXIT_FAILURE);
	if ((fd[1] = fopen("expected.log", "w")) == NULL)
		exit(EXIT_FAILURE);
	fd[2] = stdout;
	fd[3] = stdout;

	// add ft
	ft[0] = (!STDOUT ? "" : "ft_");
	ft[1] = "";

	///////////////// ft_strlen vs strlen /////////////////
	size_t	(*len[2])(const char *);
	len[0] = ft_strlen;
	len[1] = strlen;
	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], 	"\n====== %sstrlen ======\n", ft[i % 2]);
		check_strlen(fd[i], len[i % 2],
			// add string parameters here
			param,
			"abcdef",
			TERMINATE);
	}

	///////////// ft_strcpy vs strcpy //////////////////
	char *(*cpy[2])(char *, const char *);
	cpy[0] = ft_strcpy;
	cpy[1] = strcpy;
	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== %sstrcpy ======\n", ft[i % 2]);
		check_strcpy(fd[i], cpy[i % 2],
			// add string parameters here
			param,
			"aaaaaaaaaaaaaaaaaa",
			"       ",
			TERMINATE);
	}

	// /////////////* ft_strcmp vs strcmp *///////////////////
	// int (*cmp[2])(const char *, const char *);
	// cmp[0] = ft_strcmp;
	// cmp[1] = strcmp;
	// for (int i = 0; i < 2 + STDOUT; i++)
	// {
	// 	fprintf(fd[i], "\n====== %sstrcmp ========\n", ft[i % 2]);
	// 	check_strcmp(fd[i], cmp[i % 2],
	// 		//add paris of string params here
	// 		"abc", "abc",
	// 		"abc", "abcd",
	// 		"abcd", "abc",
	// 		"abcz", "abc",
	// 		"z", "abc",
	// 		"12345678901234567890zz", "12345678901234567890z",
	// 		"12345678901234567890z", "12345678901234567890z",
	// 		TERMINATE);
	// }

	// /////////////* ft_strdup vs strdup *///////////////////
	// char *(*dup[2])(const char *);
	// dup[0] = ft_strdup;
	// dup[1] = strdup;

	// for (int i = 0; i < 2 + STDOUT; i++)
	// {
	// 	fprintf(fd[i], "\n====== %sstrdup ========\n", ft[i % 2]);
	// 	check_strdup(fd[i], dup[i % 2],
	// 		// add string parameters here
	// 		param,
	// 		"abcdef",
	// 		"0",
	// 		"     ",
	// 		"\t",
	// 		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	// 		TERMINATE);
	// }

	// /////////////* ft_write vs write *///////////////////
	ssize_t (*wri[2])(int, const void *, size_t);
	wri[0] = ft_write;
	wri[1] = write;

	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== %swrite ========\n", ft[i % 2]);
		check_write(fd[i], wri[i % 2],
			// add string parameters here
			param,
			"abcdef",
			"0",
			"     ",
			"\t",
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			TERMINATE);
	}

	// /////////////* ft_read vs read *///////////////////
	// ssize_t	(*rea[2])(int, void *, size_t);
	// rea[0] = ft_read;
	// rea[1] = read;

	// for (int i = 0; i < 2 + STDOUT; i++)
	// {
	// 	fprintf(fd[i], "\n====== %sread ========\n", ft[i % 2]);
	// 	check_read(fd[i], rea[i % 2],
	// 		// add filenames and bytes here
	// 		"ft_read.s", 20,
	// 		"ft_read.s", 1,
	// 		"ft_strcmp.s", 0,
	// 		"main.c", 10,
	// 		"DNE", 20,
	// 		TERMINATE);
	// }
	return (0);
}
