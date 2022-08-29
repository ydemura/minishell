/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: znajda <znajda@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/15 14:59:17 by znajda        #+#    #+#                 */
/*   Updated: 2022/08/24 16:37:47 by znajda        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <stdlib.h>
#include <minishell.h>
#include <structs.h>
// #include <env_display.h>
// #include <env_init.h>
// #include <env_clear.h>
#include <env_copy.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <signal_handles.h>

int g_signal_status = 0;

static	void	check_leaks(void)
{
	system("leaks -quiet minishell");
	// tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}

int	main(int argc, char *argv[], char *env[])
{
	t_together All;

	(void)argc;
	(void)argv;
	All.env_array = env_copy(env);
	All.last_error = -1;
	All.head = NULL;
	All.lex_head = NULL;
	signal_director(1);
	atexit(check_leaks);
	// env_vars_copy_display(All.env_array);
	minishell(&All);
	free_lines(All.env_array);
	exit(1);
}
