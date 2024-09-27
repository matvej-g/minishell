/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:05:08 by mgering           #+#    #+#             */
/*   Updated: 2024/09/24 14:46:46 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exe(const t_cmd *cmd, t_env *env)
{
	char		**path;
	char		**tmp_path;
	t_varlst	*varlst;

	path = NULL;
	varlst = env->envp_list;
	while (varlst != NULL)
	{
		if (0 == ft_strcmp(varlst->var_name, "PATH"))
		{
			path = ft_split(varlst->var_value, ':');
			break ;
		}
		varlst = varlst->next;
	}
	tmp_path = path;
	ft_exe2(cmd, env, tmp_path);
	tmp_path = path;
	while (*tmp_path)
	{
		free(*tmp_path);
		++tmp_path;
	}
	free(path);
	exit(EXIT_FAILURE);
}

void	ft_exe2(const t_cmd *cmd, t_env *env, char **tmp_path)
{
	char		*dir_path;
	char		*tmp;

	dir_path = NULL;
	tmp = NULL;
	if (execve(cmd->args[0], cmd->args, env->envp) == -1)
	{
		tmp = ft_strjoin("/", cmd->args[0]);
		while (*tmp_path)
		{
			dir_path = ft_strjoin(*tmp_path, tmp);
			if (0 == access(dir_path, X_OK))
			{
				if (-1 == execve(dir_path, cmd->args, env->envp))
					perror("execve failed");
			}
			free(dir_path);
			++tmp_path;
		}
		free(tmp);
	}
}
