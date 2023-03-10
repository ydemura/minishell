/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_start.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:48:20 by znajda        #+#    #+#                 */
/*   Updated: 2022/09/17 15:34:23 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_START_H
# define PARSER_START_H

# include "structs.h"

t_together	*parser(char *input, t_together *all);
void		add_to_back(t_together *all, t_parse *to_add);
void		parse_display(t_parse *head);

#endif
