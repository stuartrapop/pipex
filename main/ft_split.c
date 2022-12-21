/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:35:31 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/11 10:27:53 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_number_pieces(char const *s, char c)
{
	int	count;
	int	index;
	int	in_piece;

	count = 0;
	index = 0;
	in_piece = 0;
	while (s[index] != '\0')
	{
		if (!in_piece && s[index] != (const char)c)
		{
			in_piece = 1;
			count++;
		}
		if (in_piece && s[index] == (const char)c)
			in_piece = 0;
		index++;
	}
	return (count);
}

static void	*ft_free_array(char **array_of_pieces, int piece_number)
{
	int	index;

	index = 0;
	while (index < piece_number)
	{
		free(array_of_pieces[index]);
		index++;
	}
	free(array_of_pieces);
	return (NULL);
}

static int	ft_get_piece(char **array_of_pieces, int *piece_number, \
	char const *s, char c)
{
	int		length;
	int		index;
	char	*new_piece;

	length = 0;
	index = 0;
	while (s[length] != '\0' && s[length] != (const char)c)
		length++;
	new_piece = malloc(sizeof(char) * (length + 1));
	if (new_piece == NULL)
	{
		ft_free_array(array_of_pieces, *piece_number);
		return (0);
	}
	while (s[index] != '\0' && s[index] != (const char)c)
	{
		new_piece[index] = s[index];
		index++;
	}
	new_piece[index] = '\0';
	array_of_pieces[*piece_number] = new_piece;
	(*piece_number)++;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array_of_pieces;
	int		piece_number;
	int		in_piece;

	if (s == NULL)
		return (NULL);
	array_of_pieces = malloc(sizeof(char *) * (ft_number_pieces(s, c) + 1));
	if (!array_of_pieces)
		return (NULL);
	in_piece = 0;
	piece_number = 0;
	while (*s != '\0')
	{
		if (!in_piece && *s != (const char)c)
		{
			in_piece = 1;
			if (!ft_get_piece(array_of_pieces, &piece_number, s, c))
				return (NULL);
		}
		if (in_piece && *s == (const char)c)
			in_piece = 0;
		s++;
	}
	array_of_pieces[piece_number] = NULL;
	return (array_of_pieces);
}
