/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:41:12 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/14 17:28:32 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	<string.h>

typedef struct s_pipex {
	int		fd[2];
	int		pid[2];
	char	*input_file;
	char	*output_file;
	char	**env;
	char	**params_cmd1;
	char	**params_cmd2;
	char	**paths_bin;
	char	*path_cmd1;
	char	*path_cmd2;
	int		output_fd;
	int		input_fd;

}	t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
void	ft_print_array(char *arr[]);
void	ft_print_pipex(t_pipex pipex);

#endif
