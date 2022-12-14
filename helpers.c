/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:34:31 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/14 16:04:33 by srapopor         ###   ########.fr       */
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
		printf("%s\n", arr[index]);
		index++;
	}
}

void	ft_print_pipex(t_pipex pipex)
{
	printf("input file: %s\n", pipex.input_file);
	printf("output file: %s \n", pipex.output_file);
	printf("child parameters\n");
	ft_print_array(pipex.params_cmd1);
	printf("main parameters\n");
	ft_print_array(pipex.params_cmd2);
	printf("env parameters\n");
	ft_print_array(pipex.env);
	printf("bin parameters\n");
	ft_print_array(pipex.paths_bin);
}
