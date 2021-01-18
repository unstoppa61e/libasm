/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 07:30:26 by monoue            #+#    #+#             */
/*   Updated: 2021/01/15 10:25:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_bonus.h"

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
	test_list_push_front_case("null char in the middle (\"hoge\\0hoge\")", "hoge\0hoge");
	put_test_end(title);
}

int main(void)
{
	test_list_size();
	test_list_push_front();
}
