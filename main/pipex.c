/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:16:32 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/28 12:27:13 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include <stdlib.h>
#include <errno.h>

void	ft_free_char_array(char **arr[])
{
	int	index;

	if (*arr == NULL)
		return ;
	index = 0;
	while ((*arr)[index] != NULL)
	{
		free((*arr)[index]);
		index++;
	}
	free(*arr);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	ft_waitallpids(t_pipex pipex)
{
	int		index;
	int		status;
	int		status_code;

	index = 0;
	status_code = 0;
	while (index < pipex.num_commands)
	{
		waitpid(pipex.pid[index], &status, 0);
		if (WIFEXITED(status))
		{
			status_code = WEXITSTATUS(status);
		}
		else
			status_code = 0;
		index++;
	}
	return (status_code);
}

int	ft_clean_structure(t_pipex *pipex)
{
	int	index;

	if (pipex->pipe != NULL)
		free(pipex->pipe);
	if (pipex->pid != NULL)
		free(pipex->pid);
	if (pipex->paths_bin != NULL)
		ft_free_char_array(&(pipex->paths_bin));
	index = 0;
	while (index < pipex->num_commands)
	{
		if (pipex->fd[index] != NULL)
			free(pipex->fd[index]);
		ft_free_char_array((&(pipex->cmd_param[index])));
		if (pipex->cmd_path[index] != NULL)
			free(pipex->cmd_path[index]);
		index++;
	}
	if (pipex->cmd_path != NULL)
		free(pipex->cmd_path);
	if (pipex->cmd_param != NULL)
		free(pipex->cmd_param);
	if (pipex->fd != NULL)
		free(pipex->fd);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		index;
	int		exit_code;

	if (argc < 5)
		return (ft_error("Invalid number of arguments.\n"));
	if (ft_process_args(argc, argv, env, &pipex) != 0)
		return (2);
	ft_open_pipes(&pipex);
	index = 0;
	while (index < pipex.num_commands)
	{
		pipex.pid[index] = fork();
		if (pipex.pid[index] == -1)
			return (ft_error("fork"));
		if (pipex.pid[index] == 0)
			exec_command(index, &pipex, env);
		index++;
	}
	ft_close_fds(-2, &pipex);
	exit_code = ft_waitallpids(pipex);
	ft_clean_structure(&pipex);
	return (exit_code);
}
