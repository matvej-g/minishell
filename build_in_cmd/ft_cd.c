/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:52:57 by mgering           #+#    #+#             */
/*   Updated: 2024/09/17 16:11:42 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(const t_cmd *cmd)
{
	char	*path;
	char	cwd[PATH_MAX];

	path = NULL;
	if (cmd->args[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			perror("cd: HOME not set");
			return ;
		}
	}
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
