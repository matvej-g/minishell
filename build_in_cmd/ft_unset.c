/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:48 by mgering           #+#    #+#             */
/*   Updated: 2024/10/17 13:26:46 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd, t_env *env)
{
	t_varlst	**current;
	t_varlst	*temp;
	int			i;

	i = 0;
	while (cmd->args[++i])
	{
		current = &env->envp_list;
		while (*current)
		{
			if (ft_strcmp(cmd->args[i], (*current)->var_name) == 0)
			{
				temp = *current;
				*current = (*current)->next;
				free(temp->var_name);
				free(temp->var_value);
				free(temp);
			}
			else
				current = &(*current)->next;
		}
	}
}
