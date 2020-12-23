/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 11:43:13 by sperrin           #+#    #+#             */
/*   Updated: 2020/12/23 12:42:19 by monoue           ###   ########.fr       */
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

int		strlen_test(char *str)
{
	int 	ret1;
	int 	ret2;

	ret1 = ft_strlen(str);
	ret2 = strlen(str);
	if (ret1 == ret2)
		printf("" GREEN "OK  " RESET "");
	else
		printf("" RED "KO  " RESET "");
	printf("" BLUE "strlen :" RESET" %d "YELLOW"/" RESET" "BLUE "ft_strlen :" RESET"%d \n", ret1, ret2);
	return (1);
}

int		strcpy_test(char *src)
{
	char	dest1[BUFFER_SIZE];
	char	dest2[BUFFER_SIZE];

	bzero(dest1, BUFFER_SIZE);
	bzero(dest2, BUFFER_SIZE);
	ft_strcpy(dest1, src);
	strcpy(dest2, src);

	printf("" BLUE "strcpy :" RESET" %s\n"BLUE "ft_strcpy :" RESET"%s", dest1, dest2);
	if (!strcmp(dest1, dest2))
		printf("" GREEN "     OK\n\n" RESET "");
	else
		printf("" RED "     KO\n" RESET "");
	return (1);
}

// int		strcmp_test(char *s1, char *s2)
// {
// 	int 	ret1;
// 	int 	ret2;

// 	ret1 = strcmp(s1, s2);
// 	ret2 = ft_strcmp(s1, s2);
// 	printf("" BLUE "strcmp :" RESET" %d "YELLOW"/" RESET" "BLUE "ft_strcmp :" RESET"%d ", ret1, ret2);
// 	if ((ret1 > 0 && ret2 > 0) || (ret1 < 0 && ret2 < 0) || (ret1 == 0 && ret2 == 0))
// 		printf("" GREEN "     OK\n" RESET "");
// 	else
// 		printf("" RED "     KO\n" RESET "");
// 	return (1);
// }

// int		write_test(char *str)
// {
// 	int		fd;
// 	int		fd2;
// 	int		fd3;
// 	int		fd4;

// 	fd = open("ft_write_test.txt", O_WRONLY);
// 	fd2 = open("write_test.txt", O_WRONLY);
// 	fd3 = open("wronffiledexcriptor", O_WRONLY);
// 	fd4 = open("wronffiledexcriptor", O_WRONLY);

// 	/*
// 	** STDOUT
// 	*/
// 	printf("\n"YELLOW "write" RESET" STDOUT: %zd(return value)\n", write(1, ""RED "hey" RESET"", 12));
// 	printf("\n"BLUE "ft_write" RESET" STDOUT: %zd(return value)\n\n", ft_write(1, ""RED "hey" RESET"", 12));

// 	/*
// 	** FILE DESCRIPTOR
// 	*/
// 	printf("%s\n", str);
// 	printf(""YELLOW "write" RESET" with an open file descriptor : %zd(return value)\n\n", write(fd2, str, strlen(str)));
// 	printf("%s\n", str);
// 	printf(""BLUE "ft_write" RESET" with an open file descriptor : %zd(return value)\n\n", ft_write(fd, str, strlen(str)));

// 	/*
// 	** WRONG FILE DESCRIPTOR
// 	*/
// 	printf(""YELLOW "write" RESET" with a wrong file descriptor : %zd(return value), errno : %d\n", write(fd3, str, 10), errno);
// 	printf(""BLUE "ft_write" RESET" with a wrong file descriptor : %zd(return value), errno : %d\n\n", ft_write(fd4, str, 10), errno);
// 	close(fd);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	return (1);
// }

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