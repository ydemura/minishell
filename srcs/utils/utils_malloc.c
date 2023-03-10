/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliia <yuliia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:07:48 by yuliia            #+#    #+#             */
/*   Updated: 2022/09/18 12:07:58 by yuliia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"
#include "utils_basics.h"
#include <stdio.h>
#include <stdlib.h>

char	*strdup_till_char(char *str, char c)
{
	int		i;
	char	*s2;
	int		len;

	len = strlen_till_char(str, c);
	i = 0;
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		exit(1);
	while (i < len)
	{
		s2[i] = str[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	free_array_of_str(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
