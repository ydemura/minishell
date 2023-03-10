/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_shlvl.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:32:45 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/12 15:06:16 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

char	*handle_shlvl(char *str)
{
	char	*temp;
	char	*str_hold;
	int		number;
	int		i;

	str_hold = str;
	if (!str_hold)
		return (NULL);
	i = 0;
	while (str_hold[i] != '=')
		i++;
	i++;
	number = ft_atoi(&str_hold[i]);
	str_hold[i] = '\0';
	number++;
	temp = ft_itoa(number);
	str_hold = ft_strjoin(str_hold, temp);
	free(temp);
	return (str_hold);
}
