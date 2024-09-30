/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:50:18 by mgering           #+#    #+#             */
/*   Updated: 2024/09/30 15:39:08 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	free_all(t_cmd *cmd, t_env *env)
{
	if (cmd)
		free_cmd(cmd);
	if (env)
		free_env_lst(env);
}*/

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd != NULL)
	{
		next = cmd->next;
		if (cmd->operator)
			free(cmd->operator);
		cmd->operator = NULL;
		if (cmd->args)
		{
			ft_free_split(cmd->args);
			free(cmd->args);
		}
		cmd->args = NULL;
		if (cmd->heredoc_delimiter)
			free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
		free(cmd);
		cmd = next;
	}
}
/* 
void	free_cmd_members(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		 if (cmd->operator)
			free(cmd->operator);
		if (cmd->args)
			ft_free_split(cmd->args);
		close(cmd->input_fd);
		close(cmd->output_fd);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_env_lst(t_env *env)
{
	t_varlst	*tmp;

	while (env && env->envp_list)
	{
		free(env->envp_list->var_name);
		free(env->envp_list->var_value);
		tmp = env->envp_list;
		env->envp_list = env->envp_list->next;
		free(tmp);
	}
}
 */