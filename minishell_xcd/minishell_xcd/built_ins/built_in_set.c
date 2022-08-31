//
//  built_in_set.c
//  minishell_xcd
//
//  Created by Julia Demura on 25/07/2022.
//

#include "built_in_set.h"

int	initiate_data_struct(char *command, char **envp, t_env_data *data)
{
	char *array_built_in[8];

	array_built_in[0] = "echo";
	array_built_in[1] = "cd";
	array_built_in[2] = "pwd";
	array_built_in[3] = "export";
	array_built_in[4] = "env";
	array_built_in[5] = "unset";
	array_built_in[6] = "exit";
	array_built_in[7] = NULL;
	data->comm_n = 0;
	while (data->comm_n < 7)
	{
		if (compare_str(array_built_in[data->comm_n], command) == TRU)
			break ;
		data->comm_n++;
	}
	data->num_var = find_arr_len(data->envp);
	data->envvar_repeat = 0;
	return (0);
}

char **built_in_commands(t_env_data *data)
{
	int synopsis = 1; //should be in input array

	initiate_data_struct(data->command, data->envp, data);
	if (data->comm_n == ECHO)
		echo_builtin(synopsis, data->arguments);
	else if(data->comm_n == PWD)
		pwd_builtin();
	else if (data->comm_n == EXPORT)
		export_builtin(data); ///	data->new_envp =
	else if (data->comm_n == ENV)
		env_builtin(data->envp);
	else if (data->comm_n == UNSET)
		unset_builtin(data);
	else if (data->comm_n == CD)
		cd_builtin(data);
	if (data->envp != NULL)
		free(data->envp);
	return (data->new_envp);
}

/// make error message - export and unset, same format described in export c file
