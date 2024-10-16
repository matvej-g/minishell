/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:23:00 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 15:06:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_check_args(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = cmd;
	if (tmp_cmd == NULL)
	{
		env->exit_status = g_signal_received;
		return (NULL);
	}
	if (tmp_cmd->args == NULL)
		return (NULL);
	while (tmp_cmd && 1 != env->exec_flag)
	{
		if (0 == ft_strcmp(tmp_cmd->args[0], "cd")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "export")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "unset")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "exit"))
			execute_parent(tmp_cmd, env);
		else if (tmp_cmd->next && tmp_cmd->operator
			&& 0 == ft_strcmp(tmp_cmd->operator, "|"))
			execute_pipe(&tmp_cmd, env);
		else
			execute_child(tmp_cmd, env);
		tmp_cmd = tmp_cmd->next;
	}
	return (NULL);
}

void	execute_parent(t_cmd *cmd, t_env *env)
{
	redirect_fd(cmd);
	if (0 == ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, env);
}

void	execute_child(t_cmd *cmd, t_env *env)
{
	int	pid ;

	pid = fork();
	if (pid == 0)
		child_process(cmd, env);
	else if (pid > 0)
		wait_child_process(cmd, env, pid);
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
