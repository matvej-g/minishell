/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/10/17 15:40:26 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/* void check_leaks(void)
{
    system("leaks minishell");
}
	atexit(check_leaks); */

int	main(int argc, char **argv, char **envp)
{
	t_env				*env;
	t_cmd				*cmd;

	(void)argv;
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	cmd = NULL;
	env = malloc(sizeof(t_env));
	env->envp = envp;
	init_signal_handler();
	ft_init(envp, env);
	while (1)
		shell_loop(cmd, env);
	return (0);
}

void	shell_loop(t_cmd *cmd, t_env *env)
{
	char				*input;

	g_signal_received = 0;
	input = ft_get_input(env);
	ft_check_input(input, env);
	if (input[0] != '\0')
		add_history(input);
	cmd = ft_parser(input, env);
	ft_check_args(cmd, env);
	env->exec_flag = 0;
	free_cmd(cmd);
}

/* 	print_cmd_struct(cmd);
void	print_cmd_struct(t_cmd *cmd)
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
	while (cmd->prev != NULL)
	{
		if (cmd->prev)
		{
			printf("movind to prev...;");
			cmd = cmd->prev;
			printf("%s\n", cmd->args[0]);
		}
		else
			break;
	}
}
 */