/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:02 by merdal            #+#    #+#             */
/*   Updated: 2024/10/09 13:00:48 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

int	ft_array_len(char **array, int i)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[i + len] && !ft_is_operator(array[i + len]))
		len++;
	return (len);
}
