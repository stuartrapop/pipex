/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:01:55 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 18:08:57 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "pipex.h"

int	is_separator(char c, t_parse parse)
{
	if (c == '\'' && !parse.within_double_quotes)
		return (1);
	else if (c == '\"' && !parse.within_single_quotes)
		return (1);
	else if (c == ' ' && !parse.within_single_quotes \
		&& !parse.within_double_quotes)
		return (1);
	return (0);
}

void	ft_count_pieces(char const *s, t_parse *parse)
{
	int	index;

	init_parse(parse);
	index = 0;
	while (s[index] != '\0')
	{
		if (!is_separator(s[index], *parse))
		{
			if (!parse->within_piece)
			{
				parse->within_piece = 1;
				parse->count += 1;
			}
		}
		else
		{
			if (s[index] == '\'' )
				parse->within_single_quotes = !parse->within_single_quotes;
			if (s[index] == '\"' )
				parse->within_double_quotes = !parse->within_double_quotes;
			parse->within_piece = 0;
		}
		index++;
	}
}

char	*get_piece(char *str, t_parse parse)
{
	int		index;
	int		count;
	char	*new_piece;

	count = 0;
	while (str[count] != '\0' && !is_separator(str[count], parse))
	{
		count++;
	}
	new_piece = malloc(sizeof(char) * (count + 1));
	index = 0;
	while (str[index] != '\0' && !is_separator(str[index], parse))
	{
		new_piece[index] = str[index];
		index++;
	}
	new_piece[index] = '\0';
	return (new_piece);
}

void	treat_separator(char c, t_parse *parse)
{
	if (c == '\'' )
		parse->within_single_quotes = !parse->within_single_quotes;
	if (c == '\"' )
		parse->within_double_quotes = !parse->within_double_quotes;
	parse->within_piece = 0;
}

char	**parse_params(char *arg_str)
{
	t_parse	parse;
	int		index;
	char	**arr_pieces;

	ft_count_pieces(arg_str, &parse);
	arr_pieces = malloc(sizeof(char *) * (parse.count + 1));
	init_parse(&parse);
	index = 0;
	while (arg_str[index] != 0)
	{
		if (!is_separator(arg_str[index], parse))
		{
			if (!parse.within_piece)
			{
				arr_pieces[parse.count] = get_piece(&(arg_str[index]), parse);
				parse.within_piece = 1;
				parse.count += 1;
			}
		}
		else
			treat_separator(arg_str[index], &parse);
		index++;
	}
	arr_pieces[parse.count] = NULL;
	return (arr_pieces);
}
