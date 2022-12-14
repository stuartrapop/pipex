/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:19:11 by stuartrapop       #+#    #+#             */
/*   Updated: 2022/12/14 13:20:37 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

char	*ft_strjoin(const char *s1, char const *s2 )
{
	int		length1;
	int		length2;
	int		index;
	char	*joined_str;

	length1 = ft_strlen(s1);
	length2 = ft_strlen(s2);
	index = 0;
	joined_str = malloc(sizeof(char) * (length1 + length2 + 1));
	if (!joined_str)
		return (NULL);
	while (index < length1)
	{
		joined_str[index] = s1[index];
		index++;
	}
	while (index < length1 + length2)
	{
		joined_str[index] = s2[index - length1];
		index++;
	}
	joined_str[index] = '\0';
	return (joined_str);
}
