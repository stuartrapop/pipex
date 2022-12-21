/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:31:59 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 10:29:45 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "gnl.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strdup(const char *s1)
{
	int		count;
	int		index;
	char	*dst;

	count = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[count] != '\0')
		count++;
	dst = (char *)malloc(sizeof(char) * (count + 1));
	if (dst == NULL)
		return (NULL);
	index = 0;
	while (index < count)
	{
		dst[index] = s1[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

void	ft_free_strs(char **str, char **str2, char **str3)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		index1;
	int		index2;
	char	*new_string;

	new_string = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_string)
		return (NULL);
	index1 = 0;
	index2 = 0;
	while (str1 != NULL && str1[index1] != '\0')
	{
		new_string[index1] = str1[index1];
		index1++;
	}
	while (str2 != NULL && str2[index2] != '\0')
	{
		new_string[index1 + index2] = str2[index2];
		index2++;
	}
	new_string[index1 + index2] = '\0';
	return (new_string);
}

int	ft_contains_newline(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}
