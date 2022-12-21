/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:22 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/20 14:46:52 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# if BUFFER_SIZE > 9223372036854775806
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_contains_newline(char *str);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *str1, char *str2);
void	ft_free_strs(char **str, char **str2, char **str3);

#endif