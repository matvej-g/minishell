/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:52:57 by mgering           #+#    #+#             */
/*   Updated: 2024/10/11 11:41:18 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(const t_cmd *cmd, t_env *env)
{
	char		*path;
	char		cwd[PATH_MAX];
	t_varlst	*varlst;

	varlst = env->envp_list;
	path = NULL;
	if (cmd->args[1] == NULL)
		check_home_path(varlst, &path);
	else
		path = cmd->args[1];
	if (chdir(path) != 0)
		perror("cd path");
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			setenv("PWD", cwd, 1);
		else
			perror("getcwd");
	}
}

void	check_home_path(t_varlst *varlst, char **path)
{
	while (varlst != NULL)
	{
		if (0 == ft_strcmp(varlst->var_name, "HOME"))
		{
			*path = varlst->var_value;
			break ;
		}
		varlst = varlst->next;
	}
	if (*path == NULL)
	{
		perror("cd: HOME not set");
		return ;
	}
}
