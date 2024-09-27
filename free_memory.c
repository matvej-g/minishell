/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:50:18 by mgering           #+#    #+#             */
/*   Updated: 2024/09/27 14:04:52 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_cmd *cmd, t_env *env)
{
	free_cmd(cmd);
	free_env_lst(env);
}

void	free_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->operator)
			free(cmd->operator);
		if (cmd->args)
			ft_free_split(cmd->args);
		close(cmd->input_fd);
		close(cmd->output_fd);
		cmd = cmd->next;
	}
	if (cmd)
		free(cmd);
	cmd = NULL;
}

void	free_env_lst(t_env *env)
{
	while (env->envp_list)
	{
		free(env->envp_list->var_name);
		free(env->envp_list->var_value);
		env->envp_list = env->envp_list->next;
	}
	if (env->envp_list)
		free(env->envp_list);
	if (env->envp)
		ft_free_split(env->envp);
	if (env)
		free(env);
	env = NULL;
}
