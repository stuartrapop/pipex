/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:37:24 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 17:57:33 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "gnl.h"
#include <stdlib.h>

char	**ft_get_paths(char *env[])
{
	int		index;
	char	*paths;
	char	**bin_paths;

	index = 0;
	while (env[index] != NULL)
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
		{
			paths = ft_strdup(&env[index][5]);
			if (!paths)
				return (NULL);
			bin_paths = ft_split(paths, ':');
			free(paths);
			if (!bin_paths)
				return (NULL);
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
			return (test_path);
		free(test_path);
		index++;
	}
	return (NULL);
}

int	ft_process_index_args(char *argv[], t_pipex *pipex, char *env[])
{
	int	index;

	index = 0;
	pipex->paths_bin = ft_get_paths(env);
	if (pipex->paths_bin == NULL)
		return (ft_clean_structure(pipex));
	pipex->fd = malloc(sizeof(int *) * pipex->num_commands);
	if (pipex->fd == NULL)
		return (ft_clean_structure(pipex));
	pipex->cmd_path = malloc(sizeof(char *) * pipex->num_commands);
	pipex->env = env;
	while (index < pipex->num_commands)
	{
		pipex->fd[index] = malloc(sizeof(int) * 2);
		if (pipex->fd[index] == NULL)
			return (ft_clean_structure(pipex));
		pipex->cmd_param[index] = \
			parse_params(argv[index + 2 + pipex->here_doc]);
		if (pipex->cmd_param[index] == NULL)
			return (ft_clean_structure(pipex));
		pipex->cmd_path[index] = get_path(pipex->paths_bin, \
			pipex->cmd_param[index][0]);
		index++;
	}
	return (0);
}

int	ft_process_args(int argc, char *argv[], char *env[], t_pipex *pipex)
{
	if (strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			return (ft_error("Invalid number of arguments.\n"));
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
	}
	else
		pipex->here_doc = 0;
	pipex->input_file = argv[1];
	pipex->output_file = argv[argc - 1];
	pipex->num_commands = argc - 3 - pipex->here_doc;
	pipex->pid = malloc(sizeof(int) * (pipex->num_commands + 1));
	if (pipex->pid == NULL)
		return (ft_clean_structure(pipex));
	pipex->cmd_param = malloc(sizeof(char **) * pipex->num_commands);
	if (pipex->cmd_param == NULL)
		return (ft_clean_structure(pipex));
	pipex->pipe = malloc(sizeof(int) * pipex->num_commands);
	if (pipex->pipe == NULL)
		return (ft_clean_structure(pipex));
	if (ft_process_index_args(argv, pipex, env) == 1)
		return (17);
	return (0);
}
