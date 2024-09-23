/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:05:08 by mgering           #+#    #+#             */
/*   Updated: 2024/09/23 15:18:18 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exe(const t_cmd *cmd, t_env *env)
{
	pid_t		pid;
	char		**path;
	char		**tmp_path;
	char		*tmp;
	char		*dir_path;
	t_varlst	*varlst;

	tmp = NULL;
	path = NULL;
	dir_path = NULL;
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
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->args[0], cmd->args, NULL) == -1)
		{
			tmp = ft_strjoin("/", cmd->args[0]);
			while (*path)
			{
				dir_path = ft_strjoin(*path, tmp);
				if (0 == access(dir_path, X_OK))
					if (-1 == execve(dir_path, cmd->args, NULL))
						perror("execve failed");
				free(dir_path);
				++path;
			}
		}
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait (NULL);
	else
		perror("fork failed");
	while (*tmp_path)
	{
		free(*tmp_path);
		++tmp_path;
	}
	free(tmp);
	free(path);
}
