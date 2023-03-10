/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_set.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:31:54 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:35:41 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_SET_H
# define BUILT_IN_SET_H

# include "builtin_utils.h"

int		if_is_builtin_command(char *str, char **array_built_in);
char	**enviromental_variable_function(t_exec *exec, char **arguments,
			int to_write);

#endif /* built_in_set_h */
