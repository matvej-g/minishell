/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/09/23 16:33:38 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arrays(char **arrays)
{
    if (arrays == NULL) {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; arrays[i] != NULL; i++) {
        printf("%s\n", arrays[i]);
    }
}

void print_cmd_struct(const t_cmd *cmd)
{
    int i = 0;

    while (cmd != NULL) // Loop through each command in the linked list
    {
        printf("Arguments:\n");
        i = 0; // Reset index for arguments array
        if (cmd->args)
        {
            while (cmd->args[i])
            {
                printf("  [%d]: %s\n", i, cmd->args[i]);
                i++;
            }
        }
        else
        {
            printf("  None\n");
        }
        printf("operator: %s\n", cmd->operator);
        printf("Input FD: %d\n", cmd->input_fd);
        printf("Output FD: %d\n", cmd->output_fd);

        // Move to the next command in the list, if it exists
        if (cmd->next)
        {
            printf("Moving to next command...\n");
            cmd = cmd->next;
        }
        else
        {
            printf("No next command.\n");
            break; // Exit the loop if there is no next command
        }
    }
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	*cmd;
	char 	*input;
	char 	*amk;

	env = malloc(sizeof(t_env));
	cmd = malloc(sizeof(t_cmd));
	amk = argv[0];
	env->envp = envp;
	ft_init(envp, env);
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	while (1)
	{
		input = ft_get_input();
		ft_check_input(input, env);
		add_history(input);
		cmd = ft_parser(input, env);
		print_cmd_struct(cmd);
		ft_check_args(cmd, env);
	}
	return (0);
}
