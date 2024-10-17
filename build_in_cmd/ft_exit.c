/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:58 by merdal            #+#    #+#             */
/*   Updated: 2024/10/15 12:49:10 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_alpha(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(const t_cmd *cmd, t_env *env)
{
	if (cmd->args[2])
	{
		free_env_lst(env);
		printf("exit\n");
		printf("exit: too many arguments\n");
		exit (1);
	}
	else if (ft_check_alpha(cmd->args[1]) == 1)
	{
		free_env_lst(env);
		printf("exit\nexit: wrong type\n");
		exit (255);
	}
	else if (cmd->args[1])
	{
		free_env_lst(env);
		printf("exit\n");
		exit (ft_atoi(cmd->args[1]));
	}
	else
	{
		free_env_lst(env);
		printf("exit\n");
		exit (0);
	}
}
