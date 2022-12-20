/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:41:12 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 15:51:50 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	<string.h>

typedef struct s_pipex {
	int		*pipe;
	int		**fd;
	int		*pid;
	char	*input_file;
	char	*output_file;
	char	**env;
	char	**paths_bin;
	int		num_commands;
	char	**cmd_path;
	char	***cmd_param;
	int		output_fd;
	int		input_fd;
	int		here_doc;
	char	*limiter;

}	t_pipex;

typedef struct s_parse {
	int	count;
	int	within_piece;
	int	within_single_quotes;
	int	within_double_quotes;
}	t_parse;

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
void	ft_print_array(char *arr[]);
void	ft_print_pipex(t_pipex pipex);
char	**ft_get_paths(char *env[]);
char	*get_path(char *paths[], char *operation);
int		ft_process_args(int argc, char *argv[], char *env[], t_pipex *pipex);
int		ft_close_fds(int cmd_num, t_pipex *pipex);
int		ft_stdin_from_file(t_pipex *pipex);
int		ft_stdout_to_file(t_pipex *pipex);
void	exec_command(int index, t_pipex *pipex, char *env[]);
int		ft_open_pipes(t_pipex *pipex);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_error(char *str);
int		ft_clean_structure(t_pipex *pipex);
char	**parse_params(char *arg_str);
void	init_parse(t_parse *parse);
int		ft_open_pipes(t_pipex *pipex);

#endif
