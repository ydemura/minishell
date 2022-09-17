//
//  cmd_loop.c
//  minishell_xcd
//
//  Created by Julia Demura on 03/09/2022.
//

#include "cmd_loop.h"
#include "fd_management.h"
#include "built_in_set.h"
# include <unistd.h>
#include <stdlib.h>
#include "signal_handles.h"

#include <stdio.h>

int	check_assess_to_file(const char *path)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK) < 0) ///	R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.
		return (-1);
	return (0);
}

int	loop_through_waitpid(int comm_num, t_param *params, int last_pid)
{
	int	status;
	int	p_id;
	int ex;

	ex = 0;
	p_id = last_pid;
	waitpid(p_id, &status, 0);
	if (WIFEXITED(status))
		ex = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		continue;
	return (ex);
}

void	free_exec_params(t_exec *exec)
{
	int i;

	i = 0;
	while (i < exec->comm_number)
	{
		free(exec->params[i].cmd.cmd_path);
		i++;
	}
	free(exec->params);
}

int	not_exeption_do_pipe(int i, int comm_n, t_type type)
{
	if (type == BUILTIN && comm_n == 1) ///first and builtin - I do not pipe
		return (FLS);
	else if (i == comm_n - 1)///last - I do not pipe, got rid of i == 0
		return (FLS);
	return (TRU);
}

void	fork_and_manage_child(t_exec *exec, t_param *param)
{
	param->child_pid = fork();
	if (param->child_pid < 0)
		exit(1);
	if (param->child_pid == 0)
	{
		if (check_assess_to_file(param->path_infile) < 0) ///in case of failure skip to next command
			exit(1);
		pick_a_child(exec->index, exec->comm_number, param); ///pick_fd_for_child_function
		signal_director(DEFAULT_SIG);
		if (param->cmd.type == BUILTIN)
			enviromental_variable_function(exec, param->cmd.cmd_args, param->fd);
		else
			execve(param->cmd.cmd_path, param->cmd.cmd_args, exec->envp);
		exit(1); ///if kid fails and I need to update it in order to give err number
	}
}

char	**handle_one_param_set(t_exec *exec, t_param *param, int i)
{
	char **new_envp;

	new_envp = NULL;
	if (not_exeption_do_pipe(exec->index, exec->comm_number, param[i].cmd.type) == TRU)
	{
		if (pipe(param[i].fd.pipe) < 0)
			exit(1);
	}
	if (exec->index == 0 && param->cmd.type == BUILTIN && exec->comm_number == 1)
	{
		new_envp = enviromental_variable_function(exec, param[i].cmd.cmd_args, param[i].fd);
		return (new_envp);
	}
	fork_and_manage_child(exec, param);
	manage_parent_fd(exec->index, exec->comm_number, &param[i].fd);
	return (new_envp);
}

int	go_through_commands(t_exec *exec)
{
	int i;

	i = 0;
	while (exec->index < exec->comm_number)
	{
		exec->upd_envp = handle_one_param_set(exec, exec->params, i); //xec[exec->index].params
		exec->index++;
		i++;
	}
	return (exec->params[exec->index - 1].child_pid);
}
///	at the end I expect to receive sequence of pod_t in every t_param

t_exec	creat_exec_loop_commands(t_together *input, char **envp)
{
	t_exec exec;
	int ch_pid;

	exec = form_input_for_execution(envp, input);
	// printf("Seg fault prior go through commands\n");
	signal_director(PAUSE_SIG);
	ch_pid = go_through_commands(&exec);
	exec.last_error = loop_through_waitpid(exec.comm_number, exec.params, ch_pid);
	signal_director(MAIN_SIG);
	free_exec_params(&exec);
	exec.params = NULL;
	return (exec);
}
