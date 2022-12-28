/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:40:58 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/28 10:57:26 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "gnl.h"
#include <stdlib.h>
#include <errno.h>

int	ft_close_fds(int cmd_num, t_pipex *pipex)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < pipex->num_commands)
	{
		if (pipe_index != cmd_num -1)
		{
			if (close(pipex->fd[pipe_index][0]) == -1)
			{
				ft_putnbr_fd(pipe_index, 2);
				return (ft_error("close read error\n"));
			}
		}
		if (cmd_num != pipe_index)
		{
			if (close(pipex->fd[pipe_index][1]) == -1)
			{
				ft_putnbr_fd(pipe_index, 2);
				return (ft_error("close write error\n"));
			}
		}
		pipe_index++;
	}
	return (0);
}

int	ft_stdin_from_heredoc(t_pipex *pipex)
{
	char	*buf;
	int		file;

	file = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0000666);
	if (file == -1)
		return (ft_error("pipex: problem opening temp file\n"));
	buf = NULL;
	while (1)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, pipex->limiter, ft_strlen(pipex->limiter)) == 0)
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	close(file);
	pipex->input_fd = open("heredoc.txt", O_RDONLY);
	if (pipex->input_fd == -1)
		return (ft_error("pipex: problem opening temp file\n"));
	return (0);
}

int	ft_stdin_from_file(t_pipex *pipex)
{
	if (pipex->here_doc)
		ft_stdin_from_heredoc(pipex);
	else
	{
		pipex->input_fd = open(pipex->input_file, O_RDONLY);
		if (pipex->input_fd == -1)
			return (ft_error("pipex: input: No such file or directory\n"));
	}
	if (dup2(pipex->input_fd, STDIN_FILENO) == -1)
		return (ft_error("dup error\n"));
	if (close(pipex->input_fd) == -1)
		return (ft_error("close input error\n"));
	return (0);
}

int	ft_stdout_to_file(t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->output_fd = open((const char *)(pipex->output_file), \
			O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		pipex->output_fd = open((const char *)(pipex->output_file), \
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (pipex->output_fd == -1)
	{
		close(pipex->output_fd);
		close(STDOUT_FILENO);
		return (ft_error("output error"));
	}
	if (dup2(pipex->output_fd, STDOUT_FILENO) == -1)
		return (ft_error("dup error"));
	if (close(pipex->output_fd) == -1)
		return (ft_error("closing output error"));
	return (0);
}

void	exec_command(int index, t_pipex *pipex, char *env[])
{
	ft_close_fds(index, pipex);
	if (index == 0)
	{
		if (ft_stdin_from_file(pipex) != 0)
		{
			write(pipex->fd[0][1], "\0", 1);
			close(pipex->fd[0][1]);
			exit(25);
		}
	}
	else
	{
		dup2(pipex->fd[index - 1][0], STDIN_FILENO);
		close(pipex->fd[index - 1][0]);
	}
	if (index == (pipex->num_commands - 1))
		ft_stdout_to_file(pipex);
	else
		dup2(pipex->fd[index][1], STDOUT_FILENO);
	close(pipex->fd[index][1]);
	execve(pipex->cmd_path[index], pipex->cmd_param[index], env);
	ft_error("pipex: ");
	ft_error(pipex->cmd_param[index][0]);
	ft_error(": command not found\n");
	exit(127);
}
