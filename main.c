/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:43:13 by sperrin           #+#    #+#             */
/*   Updated: 2020/12/23 13:43:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "test.h"

#define long_string "Well, there’s this passage I got memorised,\
sorta fits the occasion. Ezekiel 25:17.\
The path of the righteous man is beset on all sides by the\
iniquities of the selfish and the tyranny of evil men.\
Blessed is he who in the name of cherish and good will shepherds\
the weak through the valley of darkness for he is truly his\
keeper and the finder of lost children. And I will strike down\
upon thee with great vengeance and furious anger those who\
attempt to poison and destroy my brothers. And you will know my\
name is the Lord when I lay my vengeance upon thee."\

void	put_color(char *str, char *color)
{
	printf("%s%s"RESET, color, str);
}

void	put_ok(void)
{
	put_color("OK  ", GREEN);
}

void	put_ko(void)
{
	put_color("KO  ", RED);
}

void	strlen_test(char *str)
{
	const int ret1 = strlen(str);
	const int ret2 = ft_strlen(str);

	if (ret1 == ret2)
		put_ok();
	else
		put_ko();
	put_color("strlen: ", BLUE);
	printf("%d", ret1);
	put_color(" / ", YELLOW);
	put_color("ft_strlen: ", BLUE);
	printf("%d\n", ret2);
}

void	strcpy_test(char *src)
{
	char	dest1[BUFFER_SIZE];
	char	dest2[BUFFER_SIZE];

	bzero(dest1, BUFFER_SIZE);
	bzero(dest2, BUFFER_SIZE);
	strcpy(dest1, src);
	ft_strcpy(dest2, src);

	if (strcmp(dest1, dest2) == 0)
		put_ok();
	else
		put_ko();
	put_color("strcpy :", BLUE);
	printf("%s\n", dest1);
	put_color(" / ", YELLOW);
	put_color("ft_strcpy :", BLUE);
	printf("%s\n", dest2);
}

void	strcmp_test(char *s1, char *s2)
{
	const int ret1 = strcmp(s1, s2);
	const int ret2 = ft_strcmp(s1, s2);

	if ((ret1 > 0 && ret2 > 0) || (ret1 < 0 && ret2 < 0) || (ret1 == 0 && ret2 == 0))
		put_ok();
	else
		put_ko();
	put_color("strcmp :", BLUE);
	printf("%d\n", ret1);
	put_color(" / ", YELLOW);
	put_color("ft_strcmp :", BLUE);
	printf("%d\n", ret2);
}

void	write_test(char *str)
{
	int	fd[4];

	fd[0] = open("write_test.txt", O_WRONLY);
	fd[1] = open("ft_write_test.txt", O_WRONLY);
	fd[2] = open("wronffiledexcriptor", O_WRONLY);
	fd[3] = open("wronffiledexcriptor", O_WRONLY);

	/*
	** STDOUT
	*/
	printf("\n"YELLOW "write" RESET" STDOUT: %zd(return value)\n", write(1, ""RED "hey" RESET"", 12));
	printf("\n"BLUE "ft_write" RESET" STDOUT: %zd(return value)\n\n", ft_write(1, ""RED "hey" RESET"", 12));

	/*
	** FILE DESCRIPTOR
	*/
	printf("%s\n", str);
	put_color("write ", YELLOW);
	printf("with an open file descriptor : %zd(return value)\n\n", write(fd[1], str, strlen(str)));
	printf("%s\n", str);
	printf(""BLUE "ft_write" RESET" with an open file descriptor : %zd(return value)\n\n", ft_write(fd[0], str, strlen(str)));

	/*
	** WRONG FILE DESCRIPTOR
	*/
	printf(""YELLOW "write" RESET" with a wrong file descriptor : %zd(return value), errno : %d\n", write(fd[2], str, 10), errno);
	printf(""BLUE "ft_write" RESET" with a wrong file descriptor : %zd(return value), errno : %d\n\n", ft_write(fd[3], str, 10), errno);
	for (int i = 0; i < 4; i++)
		close(fd[i]);
}

// int		read_test(char *str)
// {
// 	char	buffer[1000];
// 	char 	buffer2[1000];
// 	int		ret;
// 	int		ret2;
// 	int		fd;
// 	int		fd2;
// 	int		fd3;
// 	int		fd4;
// 	int		ret3;
// 	int		ret4;
// 	int		ret5;
// 	int		ret6;
// 	int		ft_read_pipe[2];
// 	int		ft_read_pipe2[2];
// 	char	buf[10];

// 	/*
// 	** STDIN 
// 	*/
// 	if (pipe(ft_read_pipe) < 0)
// 		exit(EXIT_FAILURE);
// 	fcntl(ft_read_pipe[0], F_SETFL, O_NONBLOCK);
// 	write(ft_read_pipe[1], str, strlen(str));
// 	ret = read(ft_read_pipe[0], buf, 10);
// 	printf(""BLUE "read" RESET" with the stdin : %s : %d(return value)\n", buf, ret);

// 	if (pipe(ft_read_pipe2) < 0)
// 		exit(EXIT_FAILURE);
// 	fcntl(ft_read_pipe2[0], F_SETFL, O_NONBLOCK);
// 	write(ft_read_pipe2[1], str, strlen(str));
// 	ret2 = ft_read(ft_read_pipe2[0], buf, 10);
// 	printf(""YELLOW "ft_read" RESET" with the stdin : %s : %d(return value)\n\n", buf, ret2);
	

// 	/*
// 	** FILE DESCRIPTOR
// 	*/
// 	fd2 = open("write_test.txt", O_RDONLY);
// 	ret3 = read(fd2, buffer, 50);
// 	printf(""BLUE "read" RESET" with an open file descriptor : %s : %d(return value)\n", buffer, ret3);
	
// 	fd = open("ft_write_test.txt", O_RDONLY);
// 	ret4 = ft_read(fd, buffer, 50);
// 	printf(""YELLOW "ft_read" RESET" with an open file descriptor : %s : %d(return value)\n\n", buffer, ret4);
// 	close(fd);
// 	close(fd2);


// 	/*
// 	** WRONG FILE DESCRIPTOR
// 	*/
// 	fd3 = open("wrongfiledescriptor", O_RDONLY);
// 	ret5 = read(fd3, buffer2, 50);
// 	printf(""BLUE "read" RESET" with a wrong file descriptor : %s : %d(return value), errno : %d\n", buffer2, ret5, errno);

// 	fd4 = open("wrongfiledescriptor", O_RDONLY);
// 	ret6 = ft_read(fd4, buffer2, 50);
// 	printf(""YELLOW "ft_read" RESET" with a wrong file descriptor : %s : %d(return value), errno : %d\n\n", buffer2, ret6, errno);

	
// 	close(fd3);
// 	close(fd4);
// 	close(ft_read_pipe[1]);
// 	close(ft_read_pipe[0]);
// 	close(ft_read_pipe2[1]);
// 	close(ft_read_pipe2[0]);
// 	return (1);
// }

// int		strdup_test(char *str)
// {
// 	char	*str1;
// 	char	*str2;

// 	str1 = ft_strdup(str);
// 	str2 = strdup(str);
// 	printf("" BLUE "strdup :" RESET" %s\n"BLUE "ft_strdup :" RESET"%s", str1, str2);
// 	if (!strcmp(str1, str2))
// 		printf("" GREEN "     OK\n\n" RESET "");
// 	else
// 		printf("" RED "     KO\n" RESET "");
// 	free(str1);
// 	free(str2);
// 	return (1);
// }

int		main(void)
{
	/*
	** FT_STRLEN
	*/
	printf(""PURPLE "ft_strlen.s\n" RESET"");

	strlen_test("");
	strlen_test(long_string);
	printf("\n\n");

	/*
	** FT_STRCPY
	*/
	printf(""PURPLE "ft_strcpy.s\n" RESET"");
	
	strcpy_test("");
	strcpy_test(long_string);
	printf("\n\n");

	/*
	** FT_STRCMP
	*/
	// printf(""PURPLE "ft_strcmp.s\n" RESET"");

	// strcmp_test("", "");
	// strcmp_test("hello", "");
	// strcmp_test("", "word");
	// strcmp_test("hello", "hello");
	// strcmp_test("hello", "word");
	// strcmp_test("say something", "something");
	// strcmp_test("something", "say something");
	// printf("\n\n");

	/*
	** FT_WRITE
	*/
	// printf(""PURPLE "ft_write.s\n" RESET"");

	// write_test("hello word");
	// printf("\n\n");

	/*
	** FT_READ
	*/
	// printf(""PURPLE "ft_read.s\n" RESET"");
	// read_test("word hello");
	// read_test(long_string);
	// printf("\n\n");

	/*
	** FT_STRDUP
	*/
	// printf(""PURPLE "ft_strdup.s\n" RESET"");
	// strdup_test("");
	// strdup_test(long_string);
	// printf("\n\n");

}