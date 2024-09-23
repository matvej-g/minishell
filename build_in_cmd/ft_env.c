/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:27 by mgering           #+#    #+#             */
/*   Updated: 2024/09/18 17:20:37 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	t_varlst	*templst;

	templst = env->envp_list;
	while (templst)
	{
		printf("%s=%s\n", templst->var_name, templst->var_value);
		templst = templst->next;
	}
}
