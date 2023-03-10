/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:46:23 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:46:48 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_SEARCH_H
# define PATH_SEARCH_H

# include "form_exec_struct.h"

int		check_assess_to_file(const char *path);
char	**find_possible_path_options_from_envp(char **env);
char	*find_path(char *command, char **possibl_paths);
char	*find_command_path(t_cmd cmd, char **envp);

#endif /* path_search_h */
