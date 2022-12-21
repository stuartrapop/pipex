/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:34:31 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 15:51:34 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_print_array(char *arr[])
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
	{
		ft_putstr_fd(arr[index], 1);
		write(1, "\n", 1);
		index++;
	}
}

void	ft_print_pipex(t_pipex pipex)
{
	int	index;

	ft_putstr_fd("\ninput file: ", 1);
	ft_putstr_fd(pipex.input_file, 1);
	ft_putstr_fd("\noutput file: ", 1);
	ft_putstr_fd(pipex.output_file, 1);
	ft_putstr_fd("\nnum cmds: ", 1);
	ft_putnbr_fd(pipex.num_commands, 1);
	write(1, "\n", 1);
	index = 0;
	while (index < pipex.num_commands)
	{
		ft_putstr_fd("cmd parameters\n", 1);
		ft_putnbr_fd(index + 1, 1);
		write(1, "\n", 1);
		ft_print_array(pipex.cmd_param[index]);
		index++;
	}
}

void	init_parse(t_parse *parse)
{
	parse->count = 0;
	parse->within_piece = 0;
	parse->within_double_quotes = 0;
	parse->within_single_quotes = 0;
}

int	ft_open_pipes(t_pipex *pipex)
{
	int	index;

	index = 0;
	while (index < pipex->num_commands)
	{
		if (pipe(pipex->fd[index]) == -1)
			return (ft_error("pipe error\n"));
		index++;
	}
	return (0);
}
