/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:52:57 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 17:47:42 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_update_varlst(t_varlst *varlst, char *var_name, char *var_value)
{
	while (varlst)
	{
		if (strcmp(varlst->var_name, var_name) == 0)
		{
			free(varlst->var_value);
			varlst->var_value = ft_strdup(var_value);
			return ;
		}
		varlst = varlst->next;
	}
}

void	ft_update_pwd_varlst(t_varlst *varlst, char *old_pwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", old_pwd, 1);
		ft_update_varlst(varlst, "OLDPWD", old_pwd);
		setenv("PWD", cwd, 1);
		ft_update_varlst(varlst, "PWD", cwd);
	}
	else
		perror("getcwd");
}

char	*ft_get_cd_target(t_cmd *cmd, t_varlst *varlst)
{
	char	*path;

	if (cmd->args[1] == NULL)
		check_home_path(varlst, &path);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			perror("cd: OLDPWD not set");
		else
			printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	return (path);
}

void	ft_cd(t_cmd *cmd, t_env *env)
{
	char		*path;
	char		*old_pwd;
	t_varlst	*varlst;

	varlst = env->envp_list;
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	path = ft_get_cd_target(cmd, varlst);
	if (path == NULL || access(path, X_OK) != 0 || chdir(path) != 0)
	{
		ft_return_and_exit("cd: permission denied: ", 1, env);
		free(old_pwd);
		return ;
	}
	ft_update_pwd_varlst(varlst, old_pwd);
	free(old_pwd);
}
