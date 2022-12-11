/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:16:32 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/11 11:06:16 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_pipex {
	int		fd[2];
	int		pid;
	char	*child_params;
	char	*main_params;
	char	*input_file;
	char	*output_file;
	int		output_fd;
	int		input_fd;

}	t_pipex;

int	main(int argc, char *argv[])
{
	t_pipex	pipex;

	(void)argc;

	pipe(pipex.fd);
	pipex.pid = fork();

	if (pipex.pid == 0)
	{
		printf("in child process\n");
		close(pipex.fd[0]);
		close(pipex.fd[1]);
	}
	else
	{
		pipex.output_fd = open(argv[1], O_CREAT | O_WRONLY);
		dup2( pipex.output_fd, STDOUT_FILENO);
		printf("in parent process\n");
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		close(pipex.output_fd);
		wait(NULL);
	}

	printf("hello world\n");
	return (0);
}