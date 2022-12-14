/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:16:32 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/14 17:28:45 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include <stdlib.h>

void	ft_free_char_array(char **arr[])
{
	int	index;

	index = 0;
	while ((*arr)[index] != NULL)
	{
		free((*arr)[index]);
		index++;
	}
	free(*arr);
}

char	**ft_get_paths(char *env[])
{
	int		index;
	char	*paths;
	char	**bin_paths;

	index = 0;
	while (env[index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=",5) == 0)
		{
			paths = ft_strdup(&env[index][5]);
			if (!paths)
				return (NULL);
			bin_paths = ft_split(paths, ':');
			if (!bin_paths)
			{
				free(paths);
				return (NULL);
			}
			free(paths);
		}
		index++;
	}
	return (bin_paths);
}

char	*get_path(char *paths[], char *operation)
{
	char	*tmp;
	char	*test_path;
	int		index;

	index = 0;
	while (paths[index] != NULL)
	{
		tmp = ft_strjoin(paths[index], "/");
		test_path = ft_strjoin(tmp, operation);
		free(tmp);
		if (access(test_path, X_OK) == 0)
		{
			printf("bin path found %s\n", test_path);
			return (test_path);
		}
		free(test_path);
		index++;
	}
	return (NULL);
}

int	ft_process_args(int argc, char *argv[], char *env[], t_pipex *pipex)
{
	if (argc != 5)
		return (1);
	pipex->input_file = argv[1];
	pipex->output_file = argv[4];
	pipex->params_cmd1 = ft_split(argv[2], ' ');
	pipex->params_cmd2 = ft_split(argv[3], ' ');
	pipex->paths_bin = ft_get_paths(env);
	pipex->path_cmd1 = get_path(pipex->paths_bin, pipex->params_cmd1[0]);
	pipex->path_cmd2 = get_path(pipex->paths_bin, pipex->params_cmd2[0]);
	pipex->env = env;
	return (0);
}

int ft_error(char *str){
	printf("error %s \n", str);
	if (ft_strncmp(str, "pipe", 5) == 0)
		return (1);
	return (2);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	ft_process_args(argc, argv, env, &pipex);
	if (pipe(pipex.fd) == -1)
		return (ft_error("pipe"));
	pipex.pid[0] = fork();
	if (pipex.pid[0] == -1)
		return (ft_error("fork"));
	if (pipex.pid[0] == 0)
	{
		printf("in child process\n");
		pipex.input_fd = open(argv[1], O_RDONLY);
		if (pipex.input_fd == -1)
			return (ft_error("input error"));
		dup2(pipex.input_fd, STDIN_FILENO);
		dup2(pipex.fd[1], 1);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		close(pipex.input_fd);
		execve(pipex.path_cmd1, pipex.params_cmd1, env);
	}
	pipex.pid[1] = fork();
	if (pipex.pid[1] == -1)
		return (ft_error("fork"));
	if (pipex.pid[1] == 0)
	{
		printf("in 2nd child\n");
		pipex.output_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
		if (pipex.output_fd == -1)
			return (ft_error("output error"));
		dup2(pipex.output_fd, STDOUT_FILENO);
		dup2(pipex.fd[0], STDIN_FILENO);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		close(pipex.output_fd);
		//printf("file number %d\n", pipex.output_fd);
		execve(pipex.path_cmd2, pipex.params_cmd2, env);
	}
	waitpid(pipex.pid[0], 0, -1);
	waitpid(pipex.pid[1], 0, -1);
	// while (waitpid(-1, 0, 0) != -1)
	// 	continue;
	return (0);
}
