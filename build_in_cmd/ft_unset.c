/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:48 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 11:41:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd, t_env *env)
{
	t_varlst	**current;
	t_varlst	*temp;

	current = &env->envp_list;
	while (*current)
	{
		if (ft_strcmp(cmd->args[1], (*current)->var_name) == 0)
		{
			temp = *current;
			*current = (*current)->next;
			free(temp->var_name);
			free(temp->var_value);
			free(temp);
			return ;
		}
		else
			current = &(*current)->next;
	}
}
