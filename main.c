/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 07:30:26 by monoue            #+#    #+#             */
/*   Updated: 2021/01/12 16:34:07 by monoue           ###   ########.fr       */
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

void	put_color(char *str, t_colors color)
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

void	put_ok_or_ko(int result)
{
	if (result == OK)
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
	if (is_ok)
		put_ok_or_ko(OK);
	else
		put_ok_or_ko(KO);
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

void	put_test_title(char *title)
{
	put_color(">>> ", YELLOW_N);
	put_color(title, YELLOW_N);
	put_color(" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", YELLOW_N);

}

void	put_test_end(char *title)
{
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< %s end\n\n", title);
}

void	test_strlen(char *title)
{
	put_test_title(title);
	test_strlen_case("ten letters", get_specified_length_str(10));
	test_strlen_case("zero letters", get_specified_length_str(0));
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
	
	libc_dst = malloc(sizeof(char) * (strlen(test_case_str) + 1));
	if (libc_dst == NULL)
		return;
	asm_dst = malloc(sizeof(char) * (strlen(test_case_str) + 1));
	if (asm_dst == NULL)
		return;
	const char *libc_output = strcpy(libc_dst, test_case_str);
	const char *asm_output = ft_strcpy(asm_dst, test_case_str);
	const bool dst_is_ok = (strcmp(libc_dst, asm_dst) == 0);
	const bool output_is_ok = (strcmp(libc_output, asm_output) == 0);
	const bool is_ok = (dst_is_ok && output_is_ok);

	printf("  ");
	if (is_ok)
		put_ok_or_ko(OK);
	else
		put_ok_or_ko(KO);
	putchar(' ');
	put_color(case_name, PURPLE_N);
	if (is_ok)
		printf(" (dst & output: \"%s%s%s\")\n", BLUE_S, asm_output, RESET);
	else
	{
		printf("\n   ");
		if (dst_is_ok)
			put_ok_or_ko(OK);
		else
			put_ok_or_ko(KO);
		printf(" dst\n");
		if (!dst_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_dst, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_dst, RESET);
		}
		printf("   ");
		if (output_is_ok)
			put_ok_or_ko(OK);
		else
			put_ok_or_ko(KO);
		printf(" output\n");
		if (!output_is_ok)
		{
			printf("      libc: \"%s%s%s\"\n", BLUE_S, libc_output, RESET);
			printf("      asm:  \"%s%s%s\"\n", RED_S, asm_output, RESET);
		}
	}
}

void	test_strcpy(char *title)
{
	put_test_title(title);
	test_strcpy_case("basic (with new lines)", "a\nb\nc");
	test_strcpy_case("null", "");
	test_strcpy_case("max length (= 509)", get_specified_length_str(509));
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
	if (is_ok)
		put_ok_or_ko(OK);
	else
		put_ok_or_ko(KO);
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

void	test_strcmp(char *title)
{
	put_test_title(title);
	test_strcmp_case("basic_same", "hoge-XXX", "hoge-XXX");
	test_strcmp_case("basic_dif_1", "hoge-XXX", "hoge-OOO");
	test_strcmp_case("basic_dif_2", "hoge-OOO", "hoge-XXX");
	test_strcmp_case("length_dif_1", "hoge", "hogeeee");
	test_strcmp_case("length_dif_2", "hogeeee", "hoge");
	test_strcmp_case("null null", "", "");
	test_strcmp_case("normal vs null", "hoge", "");
	test_strcmp_case("null vs normal", "", "hoge");
	test_strcmp_case("max_length_same", get_specified_length_str(509), get_specified_length_str(509));
	test_strcmp_case("max_length_dif1", get_specified_length_str(508), get_specified_length_str(509));
	test_strcmp_case("max_length_dif2", get_specified_length_str(509), get_specified_length_str(508));
	put_test_end(title);
}

void	test_write_case(char *str)
{
	int		ft_write_pipe[2];
	char	buf[BUFFER_SIZE];
	int		ret;

	bzero(buf, BUFFER_SIZE);
	if (pipe(ft_write_pipe) < 0)
		exit(EXIT_FAILURE);
	fcntl(ft_write_pipe[0], F_SETFL, O_NONBLOCK);
	write(ft_write_pipe[1], str, strlen(str));
	ret = read(ft_write_pipe[0], buf, BUFFER_SIZE);
	buf[ret] = '\0';

	if (!strcmp(buf, str))
		printf("" GREEN "[OK] " RESET "");
	else
		printf("" RED "[KO] " RESET "");
	close(ft_write_pipe[1]);
	close(ft_write_pipe[0]);
}

void	test_write(char *title)
{
	put_test_title(title);
	test_write_case();
	put_test_end(title);
}


int main(void)
{
	test_strlen("strlen");
	test_strcpy("strcpy");
	test_strcmp("strcmp");
	test_write("write");
	// test_read();
	// test_strdup();
}
