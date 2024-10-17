/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:16:42 by mgering           #+#    #+#             */
/*   Updated: 2024/10/17 14:46:30 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_cmd *cmd, t_env *env)
{
	t_varlst	*templst;
	char		*var_name;
	char		*var_value;
	int			flag;
	int			i;

	i = 0;
	templst = env->envp_list;
	if (cmd->args[1] == NULL)
		cmd_export(templst);
	while (cmd->args[++i])
	{
		if (-1 == get_var_str(cmd, &var_name, &var_value, i))
		{
			env->exit_status = 1;
			return (perror("export: not a valid identifier"));
		}
		flag = check_varlst(templst, var_name, var_value, cmd->args[i]);
		if (flag == 1)
			add_varlst_node(&env->envp_list,
				new_varlst_node(var_name, var_value));
		free(var_name);
		free(var_value);
	}
}

void	cmd_export(t_varlst *templst)
{
	while (templst)
	{
		printf("declare -x %s=\"%s\"\n",
			templst->var_name, templst->var_value);
		templst = templst->next;
	}
	return ;
}

int	get_var_str(t_cmd *cmd, char **var_name, char **var_value, int i)
{
	char	**split;

	if (cmd->args[i][0] == '=')
		return (-1);
	split = ft_split(cmd->args[i], '=');
	if (split[0])
		*var_name = ft_strdup(split[0]);
	if (split [1])
		*var_value = ft_strdup(split[1]);
	else
		*var_value = ft_strdup("");
	ft_free_split(split);
	return (0);
}

int	check_varlst(t_varlst *templst, char *var_name,
		char *var_value, char *args)
{
	while (templst)
	{
		if (0 == ft_strcmp(templst->var_name, var_name)
			&& 0 == ft_strcmp(templst->var_value, var_value))
			return (0);
		if (0 == ft_strcmp(templst->var_name, var_name)
			&& NULL != ft_strchr(args, '='))
		{
			free(templst->var_value);
			templst->var_value = strdup(var_value);
			return (-1);
		}
		if (NULL == ft_strchr(args, '='))
			return (0);
		if (templst->next)
			templst = templst->next;
		else
			break ;
	}
	return (1);
}
