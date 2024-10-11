/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:39:20 by merdal            #+#    #+#             */
/*   Updated: 2024/10/10 15:31:53 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_varlst	*new_varlst_node(char *var_name, char *var_value)
{
	t_varlst	*node;

	node = (t_varlst *)malloc(sizeof(t_varlst));
	if (!node)
		return (NULL);
	node->var_name = ft_strdup(var_name);
	node->var_value = ft_strdup(var_value);
	node->next = NULL;
	return (node);
}

void	add_varlst_node(t_varlst **head, t_varlst *new_node)
{
	t_varlst	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_varlst	*ft_init_varlst(char **envp)
{
	t_varlst	*var_list;
	char		**split;
	int			i;

	var_list = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (split[0] && split[1])
		{
			add_varlst_node(&var_list, new_varlst_node(split[0], split[1]));
		}
		ft_free_split(split);
		i++;
	}
	return (var_list);
}

void	ft_init(char **envp, t_env *env)
{
	env->envp = envp;
	env->envp_list = ft_init_varlst(envp);
	env->exit_status = 0;
}
