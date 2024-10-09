/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:16:42 by mgering           #+#    #+#             */
/*   Updated: 2024/10/08 13:28:59 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(const t_cmd *cmd, t_env *env)
{
	t_varlst	*templst;
	char		*var_name;
	char		*var_value;
	int			flag;

	get_var_str(cmd, &var_name, &var_value);
	templst = env->envp_list;
	if (!var_name && !var_value)
	{
		while (templst)
		{
			printf("declare -x %s=\"%s\"\n",
				templst->var_name, templst->var_value);
			templst = templst->next;
		}
		return ;
	}
	flag = check_varlst(templst, var_name, var_value, cmd);
	if (flag == 0)
		return (free(var_name), free(var_value));
	if (flag == -1)
		return (free(var_name), free(var_value));
	if (flag == 1)
		add_varlst_node(&env->envp_list, new_varlst_node(var_name, var_value));
	return (free(var_name), free(var_value));
}

void	get_var_str(const t_cmd *cmd, char **var_name, char **var_value)
{
	char	**split;

	if (cmd->args[1] == NULL)
	{
		*var_name = NULL;
		*var_value = NULL;
		return ;
	}
	split = ft_split(cmd->args[1], '=');
	if (split[0])
		*var_name = ft_strdup(split[0]);
	if (split [1])
		*var_value = ft_strdup(split[1]);
	else
		*var_value = ft_strdup("");
	ft_free_split(split);
	return ;
}

int	check_varlst(t_varlst *templst, char *var_name,
		char *var_value, const t_cmd *cmd)
{
	while (templst)
	{
		if (0 == ft_strcmp(templst->var_name, var_name)
			&& 0 == ft_strcmp(templst->var_value, var_value))
			return (0);
		if (0 == ft_strcmp(templst->var_name, var_name)
			&& NULL != ft_strchr(cmd->args[1], '='))
		{
			free(templst->var_value);
			templst->var_value = strdup(var_value);
			return (-1);
		}
		if (0 == ft_strcmp(templst->var_name, var_name))
			return (0);
		if (templst->next)
			templst = templst->next;
		else
			break ;
	}
	return (1);
}
