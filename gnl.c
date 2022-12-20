/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:53:11 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 10:29:07 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "gnl.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_update_persist(char **persist_value, char *buf)
{
	char	*tmp;

	tmp = ft_strdup(*persist_value);
	if (*persist_value != NULL)
		ft_free_strs(persist_value, 0, 0);
	*persist_value = ft_strjoin(tmp, buf);
	ft_free_strs(&tmp, 0, 0);
	return (*persist_value);
}

void	ft_read_line(int fd, char **persist_value)
{
	char	*buf;
	int		read_response;

	buf = malloc(sizeof * buf * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	read_response = 1;
	while (read_response > 0)
	{
		read_response = read(fd, buf, BUFFER_SIZE);
		if (read_response == -1)
		{
			ft_free_strs(&buf, persist_value, 0);
			return ;
		}
		if (read_response == 0 && *persist_value == NULL)
			break ;
		buf[read_response] = '\0';
		*persist_value = ft_update_persist(persist_value, buf);
		if (ft_contains_newline(*persist_value))
			break ;
	}
	ft_free_strs(&buf, 0, 0);
}

char	*ft_get_before_nl(char *persist_value)
{
	int		index;
	int		count;
	char	*before_string;

	index = 0;
	count = 0;
	while (persist_value[count] != '\0' && persist_value[count] != '\n')
		count++;
	if (persist_value[count] == '\n')
		count++;
	before_string = malloc(sizeof(char) * (count + 1));
	if (!before_string)
		return (NULL);
	index = 0;
	while (index < count)
	{
		before_string[index] = persist_value[index];
		index++;
	}
	before_string[index] = '\0';
	return (before_string);
}

char	*ft_get_after_nl(char *persist_value)
{
	int		index;
	int		count;
	int		length;
	char	*after_string;

	index = 0;
	count = 0;
	length = ft_strlen(persist_value);
	while (persist_value[count] != '\0' && persist_value[count] != '\n')
		count++;
	if (persist_value[count] == '\n')
		count++;
	if (count == 0 || persist_value[count] == '\0')
		return (NULL);
	after_string = malloc(sizeof(char) * (length - count + 1));
	if (!after_string)
		return (NULL);
	index = 0;
	while ((index + count) < length)
	{
		after_string[index] = persist_value[index + count];
		index++;
	}
	after_string[index] = '\0';
	return (after_string);
}

char	*get_next_line(int fd)
{
	static char	*persist_value = NULL;
	char		*full_line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	full_line = NULL;
	ft_read_line(fd, &persist_value);
	if (persist_value == NULL)
		return (NULL);
	full_line = ft_get_before_nl(persist_value);
	tmp = ft_get_after_nl(persist_value);
	if (!full_line || *full_line == '\0')
	{
		ft_free_strs(&persist_value, &full_line, &tmp);
		return (NULL);
	}
	ft_free_strs(&persist_value, 0, 0);
	persist_value = tmp;
	return (full_line);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	(void) argc;
// 	fd = open(argv[1], O_RDONLY);
// 	line = "";
// 	while (line != NULL)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 	}
// 	printf("BUFFER_SIZE %d\n", BUFFER_SIZE);
// 	fd = close(fd);
// 	return (0);
// }
