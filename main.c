/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 07:30:26 by monoue            #+#    #+#             */
/*   Updated: 2021/01/14 15:24:12 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

const char *color_strs[COLORS_NUM] = {
	RED_S,
	GREEN_S,
	YELLOW_S,	
	BLUE_S,
	PURPLE_S,
	CYAN_S
};

void	put_color(const char *str, t_colors color)
{
	printf("%s%s%s", color_strs[color], str, RESET);
}

char	*get_specified_length_str(size_t len)
{
	size_t	index;
	char	*str; // the minimum length required for ANSI compability

	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	for (size_t index = 0; index < len; index++)
		str[index] = 'X';
	str[len] = '\0';
	return (str);
}

char	*ctos(char c)
{
	char *str;

	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\n';
	return (str);
}

void	put_ok_or_ko(bool is_ok)
{
	if (is_ok)
		put_color("OK", GREEN_N);
	else
		put_color("KO", RED_N);
}

// << strlen >>
// OK ten letters (output: 10)
// KO max length (= 509)
//    libc: 509
//    asm:  512
// --- strlen test end ---
//

void	test_strlen_case(char *case_name, char *test_case_str)
{
	const size_t	libc_output = strlen(test_case_str);
	const size_t	asm_output = ft_strlen(test_case_str);
	const bool		is_ok = (libc_output == asm_output);
	
	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		printf(" (output: %s%zu%s)\n", BLUE_S, asm_output, RESET);
	else
	{
		putchar('\n');
		printf("   libc: %s%zu%s\n", BLUE_S, libc_output, RESET);
		printf("   asm:  %s%zu%s\n", RED_S, asm_output, RESET);
		putchar('\n');
	}
}

void	put_test_title(const char *title)
{
	put_color(">>> ", YELLOW_N);
	put_color(title, YELLOW_N);
	put_color(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", YELLOW_N);

}

void	put_test_end(const char *title)
{
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< %s end\n\n", title);
}

void	test_strlen()
{
	const char *title = "strlen";

	put_test_title(title);
	test_strlen_case("ten letters", get_specified_length_str(10));
	test_strlen_case("zero letters", get_specified_length_str(0));
	test_strlen_case("null char in the middle", "hoge\0hoge");
	test_strlen_case("max length (= 509)", get_specified_length_str(509));
	put_test_end(title);
}

// << strcpy >>
// OK basic (dst & output: "a\nb\nc")
// KO max length (= 509)
//	  OK dst
//    KO output
//    	libc: "abc"
//    	asm:  "abcdefg"
// --- strcpy test end ---
//
void	test_strcpy_case(char *case_name, char *test_case_str)
{
	char	*libc_dst;
	char	*asm_dst;
	
	libc_dst = get_specified_length_str(strlen(test_case_str) + 3);
	asm_dst = get_specified_length_str(strlen(test_case_str) + 3);

	const char *libc_output = strcpy(libc_dst, test_case_str);
	const char *asm_output = ft_strcpy(asm_dst, test_case_str);
	const bool dst_is_ok = (strcmp(libc_dst, asm_dst) == 0);
	const bool output_is_ok = (strcmp(libc_output, asm_output) == 0);
	const bool is_ok = (dst_is_ok && output_is_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		// printf(" (dst & output: \"%s%s%s\")\n", BLUE_S, asm_output, RESET);
		printf(" (dst: \"%s%s%s\", output: \"%s%s%s\")\n", BLUE_S, asm_dst, RESET, BLUE_S, asm_output, RESET);
	else
	{
		printf("\n   ");
		put_ok_or_ko(dst_is_ok);
		printf(" dst\n");
		if (!dst_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_dst, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_dst, RESET);
		}
		printf("   ");
		put_ok_or_ko(output_is_ok);
		printf(" output\n");
		if (!output_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_output, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_output, RESET);
		}
	}
}

void	test_strcpy_case_less_malloc_space(char *case_name, const char *test_case_str)
{
	char	*libc_dst;
	char	*asm_dst;
	
	libc_dst = get_specified_length_str(strlen(test_case_str) - 3);
	asm_dst = get_specified_length_str(strlen(test_case_str) - 3);

	const char *libc_output = strcpy(libc_dst, test_case_str);
	const char *asm_output = ft_strcpy(asm_dst, test_case_str);
	const bool dst_is_ok = (strcmp(libc_dst, asm_dst) == 0);
	const bool output_is_ok = (strcmp(libc_output, asm_output) == 0);
	const bool is_ok = (dst_is_ok && output_is_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		// printf(" (dst & output: \"%s%s%s\")\n", BLUE_S, asm_output, RESET);
		printf(" (dst: \"%s%s%s\", output: \"%s%s%s\")\n", BLUE_S, asm_dst, RESET, BLUE_S, asm_output, RESET);
	else
	{
		printf("\n   ");
		put_ok_or_ko(dst_is_ok);
		printf(" dst\n");
		if (!dst_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_dst, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_dst, RESET);
		}
		printf("   ");
		put_ok_or_ko(output_is_ok);
		printf(" output\n");
		if (!output_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_output, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_output, RESET);
		}
	}
}

void	test_strcpy_changing_char(char *case_name, const char *test_case_str)
{
	char	*libc_dst;
	char	*asm_dst;
	
	libc_dst = get_specified_length_str(strlen(test_case_str) + 3);
	asm_dst = get_specified_length_str(strlen(test_case_str) + 3);

	char *libc_output = strcpy(libc_dst, test_case_str);
	char *asm_output = ft_strcpy(asm_dst, test_case_str);
	libc_output[0] = 'Z';
	asm_output[0] = 'Z';
	const bool dst_is_ok = (strcmp(libc_dst, asm_dst) == 0);
	const bool output_is_ok = (strcmp(libc_output, asm_output) == 0);
	const bool is_ok = (dst_is_ok && output_is_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		// printf(" (dst & output: \"%s%s%s\")\n", BLUE_S, asm_output, RESET);
		printf(" (dst: \"%s%s%s\", output: \"%s%s%s\")\n", BLUE_S, asm_dst, RESET, BLUE_S, asm_output, RESET);
	else
	{
		printf("\n   ");
		put_ok_or_ko(dst_is_ok);
		printf(" dst\n");
		if (!dst_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_dst, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_dst, RESET);
		}
		printf("   ");
		put_ok_or_ko(output_is_ok);
		printf(" output\n");
		if (!output_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_output, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_output, RESET);
		}
	}
}

void	test_strcpy()
{
	const char *title = "strcpy";
	const char *basic = "a\nb\nc";

	put_test_title(title);
	test_strcpy_case("basic (with new lines)", "a\nb\nc");
	test_strcpy_case("null", "");
	test_strcpy_case("null char in the middle", "hoge\0hoge");
	test_strcpy_case("max length (= 509)", get_specified_length_str(509));
	test_strcpy_case_less_malloc_space("basic (with less malloc space)", basic);
	test_strcpy_case_less_malloc_space("max length (with less malloc space)", get_specified_length_str(509));
	test_strcpy_changing_char("basic (changing the first character)", basic);
	test_strcpy_changing_char("max length (changing the first character)", get_specified_length_str(509));
	put_test_end(title);
}

bool	is_strcmp_ok(const int libc_output, const int asm_output)
{
	if (libc_output > 0 && asm_output > 0)
		return (true);
	if (libc_output < 0 && asm_output < 0)
		return (true);
	if (libc_output == 0 && asm_output == 0)
		return (true);
	return (false);
}

void	test_strcmp_case(char *case_name, char *s1, char *s2)
{
	const int	libc_output = strcmp(s1, s2);
	const int	asm_output = ft_strcmp(s1, s2);
	const bool	is_ok = is_strcmp_ok(libc_output, asm_output);
	
	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		printf(" (libc: %s%d%s, asm: %s%d%s)\n", BLUE_S, libc_output, RESET, BLUE_S, asm_output, RESET);
	else
	{
		putchar('\n');
		printf("   libc: %s%d%s\n", BLUE_S, libc_output, RESET);
		printf("   asm:  %s%d%s\n", RED_S, asm_output, RESET);
		putchar('\n');
	}
}

void	test_strcmp()
{
	const char *title = "strcmp";

	put_test_title(title);
	test_strcmp_case("basic_same", "hoge-XXX", "hoge-XXX");
	test_strcmp_case("basic_dif_1", "hoge-XXX", "hoge-OOO");
	test_strcmp_case("basic_dif_2", "hoge-OOO", "hoge-XXX");
	test_strcmp_case("length_dif_1", "hoge", "hogeeee");
	test_strcmp_case("length_dif_2", "hogeeee", "hoge");
	test_strcmp_case("both null", "", "");
	test_strcmp_case("null char in the middle_1", "hoge\0hoge", "hoge\0hoge");
	test_strcmp_case("null char in the middle_1", "hoge\0hoge", "hoge\0fuga");
	test_strcmp_case("normal vs null", "hoge", "");
	test_strcmp_case("null vs normal", "", "hoge");
	test_strcmp_case("max_length_same", get_specified_length_str(509), get_specified_length_str(509));
	test_strcmp_case("max_length_dif1", get_specified_length_str(508), get_specified_length_str(509));
	test_strcmp_case("max_length_dif2", get_specified_length_str(509), get_specified_length_str(508));
	put_test_end(title);
}

void	test_write_case(char *case_name, char const *str, size_t count)
{
	int fds[2];
	ssize_t write_rets[2];
	ssize_t read_rets[2];
	int errnos[2];
	typedef ssize_t (*t_write)(int, const void*, size_t);
	t_write funcs[2] = {write, ft_write};
	const char *filenames[2] = {"linux_write_output", "ft_write_output"};
	// char bufs[2][BUFFER_SIZE];
	char bufs[2][BUFFER];

	for (int i = 0; i < 2; i++)
	{
		fds[i] = open(filenames[i], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fds[i] == ERROR)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		fcntl(fds[i], F_SETFL, O_NONBLOCK);
		errnos[i] = 0;
		write_rets[i] = funcs[i](fds[i], str, count);
		errnos[i] = errno;
		// bzero(bufs[i], BUFFER_SIZE);
		bzero(bufs[i], BUFFER);
		// read_rets[i] = read(fds[i], bufs[i], BUFFER_SIZE);
		read_rets[i] = read(fds[i], bufs[i], BUFFER);
		bufs[i][read_rets[i]] = '\0';
		close(fds[i]);
	}
	const bool is_output_ok = (strcmp(bufs[0], bufs[1]) == 0);
	const bool is_ret_ok = (write_rets[0] == write_rets[1]);
	const bool is_errno_ok = (errnos[0] == errnos[1]);
	const bool is_ok = (is_output_ok && is_ret_ok && is_errno_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
	{
		if (errnos[1] != 0)	
			printf(" errno: %s%d%s", BLUE_S, errnos[1], RESET);
	}
	else
	{
		printf("\n   ");
		put_ok_or_ko(is_output_ok);
		printf(" output\n");
		if (!is_output_ok)
		{
			printf("      linux: \"%s%s%s\"\n", BLUE_S, bufs[0], RESET);
			printf("      asm:   \"%s%s%s\"\n", RED_S, bufs[1], RESET);
		}
		printf("   ");
		put_ok_or_ko(is_ret_ok);
		printf(" return value\n");
		if (!is_ret_ok)
		{
			printf("      linux: \"%s%zd%s\"\n", BLUE_S, write_rets[0], RESET);
			printf("      asm:   \"%s%zd%s\"\n", RED_S, write_rets[1], RESET);
		}
		printf("   ");
		put_ok_or_ko(is_errno_ok);
		printf(" errno\n");
		if (!is_errno_ok)
		{
			printf("      linux: \"%s%d%s\"\n", BLUE_S, errnos[0], RESET);
			printf("      asm:   \"%s%d%s\"\n", RED_S, errnos[1], RESET);
		}
	}
	putchar('\n');
}

void	test_write_signed_fd(char *case_name, int fd, char *str_name, char const *str, size_t count)
{
	int		errnos[2];
	typedef ssize_t (*t_write)(int, const void*, size_t);
	t_write funcs[2] = {write, ft_write};

	for (int i = 0; i < 2; i++)
	{
		errnos[i] = 0;
		funcs[i](fd, str, count);
		errnos[i] = errno;
	}
	const bool is_ok = (errnos[0] == errnos[1]);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	printf(" %s(fd: %d, str: %s, count: %zu)%s ", PURPLE_S, fd, str_name, count, RESET);
	if (is_ok)
		printf("errno: %s%d%s", BLUE_S, errnos[1], RESET);
	else
	{
		printf("      linux errno: \"%s%d%s\"\n", BLUE_S, errnos[0], RESET);
		printf("      asm   errno:   \"%s%d%s\"\n", RED_S, errnos[1], RESET);
	}
	putchar('\n');
}

void	test_write()
{
	const char *title = "write";

	const char *basic = "a\nb\nc";
	const char *max_length = get_specified_length_str(512);
	const char *empty = "";
	const char *null_char_in_the_middle = "hoge\0hoge";

	put_test_title(title);
	test_write_case("basic (\"a\\nb\\nc\", len)", basic, strlen(basic));
	test_write_case("empty (\"\", len)", empty, strlen(empty));
	test_write_case("null char in the middle", null_char_in_the_middle, 100);
	test_write_case("count shorter than actual (\"a\\nb\\nc\", len - 2)", basic, strlen(basic) - 2);
	test_write_case("count longer than actual (\"a\\nb\\nc\", len + 2)", basic, strlen(basic) + 2);
	test_write_case("max length ('X' * 512, len)", max_length, strlen(max_length));
	test_write_case("count_zero (basic, 0)", basic, 0);
	test_write_case("count_signed_01 (basic, -1)", basic, -1);
	test_write_case("count_signed_02 (basic, -10)", basic, -10);
	test_write_case("count_signed_03 (basic, -100)", basic, -100);
	test_write_case("count_signed_04 (basic, -1000)", basic, -1000);
	test_write_case("count_signed_05 (basic, -10000)", basic, -10000);
	test_write_case("count_signed_06 (basic, -100000)", basic, -100000);
	test_write_case("count_signed_07 (basic, -1000000)", basic, -1000000);
	test_write_case("count_signed_08 (basic, -10000000)", basic, -10000000);
	test_write_case("count_signed_09 (basic, -100000000)", basic, -100000000);
	test_write_case("count_signed_10 (basic, -1000000000)", basic, -1000000000);
	test_write_case("count_signed_11 (basic, -10000000000)", basic, -10000000000);
	test_write_case("count_signed_12 (basic, -100000000000)", basic, -100000000000);
	test_write_signed_fd("fd_signed_01", -1, "basic", basic, 0);
	test_write_signed_fd("fd_signed_02", -10, "max_length", max_length, -10);
	test_write_signed_fd("fd_signed_03", -100, "empty", empty, 50);
	test_write_signed_fd("fd_signed_04", -1000, "basic", basic, 10);
	test_write_signed_fd("fd_signed_05", -10000, "empty", empty, 100);
	test_write_signed_fd("fd_signed_06", -100000, "max_length", max_length, -500);
	test_write_signed_fd("fd_signed_07", -1000000, "basic", basic, -10000);
	test_write_signed_fd("fd_signed_08", -10000000, "empty", empty, 1000);
	test_write_signed_fd("fd_signed_09", -100000000, "max_length", max_length, -50000000000000);
	test_write_signed_fd("fd_signed_10", -1000000000, "basic", basic, 100);
	put_test_end(title);
}

void	test_read_fixing_buf(char *case_name, char const *str, size_t count)
{
	int fds[2];
	ssize_t rets[2];
	int errnos[2];
	typedef ssize_t (*t_read)(int, void*, size_t);
	t_read funcs[2] = {read, ft_read};
	const char *filenames[2] = {"linux_read_output", "ft_read_output"};
	// char bufs[2][BUFFER_SIZE];
	char bufs[2][BUFFER];

	for (int i = 0; i < 2; i++)
	{
		fds[i] = open(filenames[i], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fds[i] == ERROR)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		fcntl(fds[i], F_SETFL, O_NONBLOCK);
		write(fds[i], str, count);
		// bzero(bufs[i], BUFFER_SIZE);
		bzero(bufs[i], BUFFER);
		errnos[i] = 0;
		rets[i] = funcs[i](fds[i], bufs[i], BUFFER);
		// rets[i] = funcs[i](fds[i], bufs[i], BUFFER_SIZE);
		errnos[i] = errno;
		bufs[i][rets[i]] = '\0';
		close(fds[i]);
	}
	const bool is_output_ok = (strcmp(bufs[0], bufs[1]) == 0);
	const bool is_ret_ok = (rets[0] == rets[1]);
	const bool is_errno_ok = (errnos[0] == errnos[1]);
	const bool is_ok = (is_output_ok && is_ret_ok && is_errno_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
	{
		if (errnos[1] != 0)	
			printf(" errno: %s%d%s", BLUE_S, errnos[1], RESET);
	}
	else
	{
		printf("\n   ");
		put_ok_or_ko(is_output_ok);
		printf(" output\n");
		if (!is_output_ok)
		{
			printf("      linux: \"%s%s%s\"\n", BLUE_S, bufs[0], RESET);
			printf("      asm:   \"%s%s%s\"\n", RED_S, bufs[1], RESET);
		}
		printf("   ");
		put_ok_or_ko(is_ret_ok);
		printf(" return value\n");
		if (!is_ret_ok)
		{
			printf("      linux: \"%s%zd%s\"\n", BLUE_S, rets[0], RESET);
			printf("      asm:   \"%s%zd%s\"\n", RED_S, rets[1], RESET);
		}
		printf("   ");
		put_ok_or_ko(is_errno_ok);
		printf(" errno\n");
		if (!is_errno_ok)
		{
			printf("      linux: \"%s%d%s\"\n", BLUE_S, errnos[0], RESET);
			printf("      asm:   \"%s%d%s\"\n", RED_S, errnos[1], RESET);
		}
	}
	putchar('\n');
}

void	test_read_varying_buf(char *case_name, int fd, int buffer_size, size_t count)
{
	int		errnos[2];
	typedef ssize_t (*t_read)(int, void*, size_t);
	t_read	funcs[2] = {read, ft_read};
	char bufs[2][buffer_size];

	for (int i = 0; i < 2; i++)
	{
		errnos[i] = 0;
		funcs[i](fd, bufs[i], count);
		errnos[i] = errno;
	}
	const bool is_ok = (errnos[0] == errnos[1]);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	printf(" %s(fd: %d, buffer_size: %d, count: %zu)%s ", PURPLE_S, fd, buffer_size, count, RESET);
	if (is_ok)
		printf("errno: %s%d%s", BLUE_S, errnos[1], RESET);
	else
	{
		printf("      linux errno: \"%s%d%s\"\n", BLUE_S, errnos[0], RESET);
		printf("      asm   errno:   \"%s%d%s\"\n", RED_S, errnos[1], RESET);
	}
	putchar('\n');
}

void	test_read()
{
	const char *title = "read";

	const char *basic = "a\nb\nc";
	const char *max_length = get_specified_length_str(512);
	const char *empty = "";
	const char *null_char_in_the_middle = "hoge\0hoge";

	put_test_title(title);
	test_read_fixing_buf("basic (\"a\\nb\\nc\", len)", basic, strlen(basic));
	test_read_fixing_buf("empty (\"\", len)", empty, strlen(empty));
	test_read_fixing_buf("null char in the middle (\"hoge\\0hoge\", 100)", null_char_in_the_middle, 100);
	test_read_fixing_buf("count shorter than actual (\"a\\nb\\nc\", len - 2)", basic, strlen(basic) - 2);
	test_read_fixing_buf("count longer than actual (\"a\\nb\\nc\", len + 2)", basic, strlen(basic) + 2);
	test_read_fixing_buf("max length ('X' * 512, len)", max_length, strlen(max_length));
	test_read_fixing_buf("count_zero (basic, 0)", basic, 0);
	test_read_fixing_buf("count_signed_01 (basic, -1)", basic, -1);
	test_read_fixing_buf("count_signed_02 (basic, -10)", basic, -10);
	test_read_fixing_buf("count_signed_03 (basic, -100)", basic, -100);
	test_read_fixing_buf("count_signed_04 (basic, -1000)", basic, -1000);
	test_read_fixing_buf("count_signed_05 (basic, -10000)", basic, -10000);
	test_read_fixing_buf("count_signed_06 (basic, -100000)", basic, -100000);
	test_read_fixing_buf("count_signed_07 (basic, -1000000)", basic, -1000000);
	test_read_fixing_buf("count_signed_08 (basic, -10000000)", basic, -10000000);
	test_read_fixing_buf("count_signed_09 (basic, -100000000)", basic, -100000000);
	test_read_fixing_buf("count_signed_10 (basic, -1000000000)", basic, -1000000000);
	test_read_fixing_buf("count_signed_11 (basic, -10000000000)", basic, -10000000000);
	test_read_fixing_buf("count_signed_12 (basic, -100000000000)", basic, -100000000000);
	test_read_varying_buf("fd_zero", 10000, 0, 100); // これは残す
	test_read_varying_buf("fd_signed_1", -1, 100, 0);
	test_read_varying_buf("fd_signed_2", -100, 500, 50);
	test_read_varying_buf("fd_signed_3", -10000, 0, 100);
	test_read_varying_buf("fd_signed_4", -1000000000, 1000, 100);

	// all the cases below invoke segv with the original read
	// test_read_varying_buf("segv_01", 1, -100, 0);
	// test_read_varying_buf("segv_02", 10, -100, -10);
	// test_read_varying_buf("segv_03", 100, -500, 50);
	// test_read_varying_buf("segv_04", 1000, -1000000000, 10);
	// test_read_varying_buf("segv_05", 100000, -10, -500);
	// test_read_varying_buf("segv_06", 1000000, -1000000, -10000);
	// test_read_varying_buf("segv_07", 10000000, -1, 1000);
	// test_read_varying_buf("segv_08", 100000000, -1, -50000000000000);
	// test_read_varying_buf("segv_09", 1000000000, -1000, 100);
	// test_read_varying_buf("segv_10", -10, -100, -10);
	// test_read_varying_buf("segv_11", -1000, 1000000000, 10);
	// test_read_varying_buf("segv_12", -100000, -10, -500);
	// test_read_varying_buf("segv_13", -1000000, -1000000, -10000);
	// test_read_varying_buf("segv_14", -10000000, 1, 1000);
	// test_read_varying_buf("segv_15", -100000000, -1, -50000000000000);
	put_test_end(title);
}

void	test_strdup_case(char *case_name, const char *test_case_str)
{
	const char *libc_ret = strdup(test_case_str);
	const char *asm_ret = ft_strdup(test_case_str);
	
	const bool is_ok = (strcmp(libc_ret, asm_ret) == 0);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		;
	else
	{
		putchar('\n');
		printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_ret, RESET);
		printf("      asm:  \"%s%s%s\"\n", RED_S, asm_ret, RESET);
	}
	putchar('\n');
}

void	test_strdup(void)
{
	const char *title = "strdup";

	const char *basic = "abcde";

	put_test_title(title);
	test_strdup_case("basic: \"abcde\"", basic);
	test_strdup_case("empty: \"\"", "");
	test_strdup_case("null char in the middle: \"hoge\\0hoge\"", "hoge\0hoge");
	test_strdup_case("max_length: (X * 509)", get_specified_length_str(509));
	put_test_end(title);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		list_size(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_list_add_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

t_list	*ft_list_new(void *data)
{
	t_list		*lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void	test_list_size_case(char *case_name, int lst_num)
{
	t_list	*list;
	int		count;

	count = 0;
	list = NULL;
	while (count < lst_num)
	{
		ft_list_add_back(&list, ft_list_new(&count));
		count++;
	}

	const int expected_size = list_size(list);
	const int asm_size = ft_list_size(list);
	const bool is_ok = (expected_size == asm_size);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		;
	else
	{
		putchar('\n');
		printf("      expected: \"%s%d%s\"\n", BLUE_S, expected_size, RESET);
		printf("      asm:      \"%s%d%s\"\n", RED_S, asm_size, RESET);
	}
	putchar('\n');
}

void	test_list_size(void)
{
	const char *title = "list_size";

	put_test_title(title);
	test_list_size_case("1", 1);
	test_list_size_case("5", 5);
	test_list_size_case("0", 0);
	test_list_size_case("100", 100);
	put_test_end(title);
}

void	list_push_front(t_list **begin_list, void *data)
{
	t_list	*list_head;

	if (!begin_list || !data)
		return ;
	list_head = ft_list_new(data);
	list_head->next = *begin_list;
	*begin_list = list_head;
}

void	test_list_push_front_case(char *case_name, char *str)
{
	t_list	*lists[2];
	int		counts[2];
	typedef void (*t_list_push_front)(t_list **, void *);
	t_list_push_front funcs[2] = {list_push_front, ft_list_push_front};

	
	for (int i = 0; i < 2; i++)
	{
		lists[i] = ft_list_new("libasm");
		ft_list_add_back(&lists[i], ft_list_new("test"));
		ft_list_add_back(&lists[i], ft_list_new("is"));
		funcs[i](&lists[i], "going");
		counts[i] = list_size(lists[i]);
	}
	const bool is_count_ok = (counts[0] == counts[1]);
	bool is_data_ok = true;
	for (int i = 0; i < counts[0]; i++)
	{
		if (strcmp(lists[0]->data, lists[1]->data) != 0)	
		{
			is_data_ok = false;
			break ;
		}
	}
	const bool is_ok = (is_count_ok && is_data_ok);

	printf("  ");
	put_ok_or_ko(is_ok);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		;
	else
	{
		printf("\n   ");
		put_ok_or_ko(is_count_ok);
		printf(" count\n");
		if (!is_count_ok)
		{
			printf("      expected: \"%s%d%s\"\n", BLUE_S, counts[0], RESET);
			printf("      asm:      \"%s%d%s\"\n", RED_S, counts[1], RESET);
		}
		printf("   ");
		put_ok_or_ko(is_data_ok);
		printf(" data\n");
		if (!is_data_ok)
		{
			for (int i = 0; i < counts[0]; i++)
			{
				const char *expected_data = lists[0]->data;
				const char *asm_data = lists[1]->data;

				printf("      %d) ", i);
				const bool is_this_data_ok = (strcmp(expected_data, asm_data) == 0);
				put_ok_or_ko(is_this_data_ok);
				if (!is_this_data_ok)
				{
					printf(" expected: \"%s%s%s\",", BLUE_S, lists[0]->data, RESET);
					printf(" asm:   	\"%s%s%s\"\n", RED_S, lists[1]->data, RESET);
				}
				lists[0] = lists[0]->next;
				lists[1] = lists[1]->next;
				putchar('\n');
			}
		}
	}
	putchar('\n');
}

void	test_list_push_front(void)
{
	const char *title = "push_front";

	put_test_title(title);
	test_list_push_front_case("basic (\"a\\nb\\nc\")", "a\nb\nc");
	test_list_push_front_case("empty", "");
	test_list_push_front_case("null char in the middle (\"hoge\0hoge\")", "hoge\0hoge");
	put_test_end(title);
}

int main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	test_list_size();
	test_list_push_front();
}
