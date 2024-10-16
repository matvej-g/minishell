/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:50:18 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 15:09:09 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		i = -1;
		temp = cmd;
		cmd = cmd->next;
		if (temp->operator)
			free(temp->operator);
		if (temp->heredoc_delimiter)
			free(temp->heredoc_delimiter);
		if (temp->args)
		{
			while (temp->args[++i])
				free(temp->args[i]);
			free(temp->args);
		}
		free(temp);
	}
}

void	free_env_lst(t_env *env)
{
	t_varlst	*temp;
	t_varlst	*next;	

	temp = env->envp_list;
	while (temp)
	{
		next = temp->next;
		if (temp->var_name)
			free(temp->var_name);
		if (temp->var_value)
			free(temp->var_value);
		free(temp);
		temp = next;
	}
	free(env);
}
