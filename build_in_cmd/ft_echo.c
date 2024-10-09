/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:22:46 by mgering           #+#    #+#             */
/*   Updated: 2024/10/08 12:18:45 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(const t_cmd *cmd)
{
	char	*str_struct;

	if (0 == ft_strcmp(cmd->args[1], "-n"))
	{
		str_struct = ft_append_char_struct(cmd, 1);
		printf("%s", str_struct);
	}
	else
	{
		str_struct = ft_append_char_struct(cmd, 0);
		printf("%s\n", str_struct);
	}
	if (str_struct)
		free(str_struct);
}

char	*ft_append_char_struct(const t_cmd *cmd, int i)
{
	char	*append;
	int		len;
	int		n;
	int		j;

	len = 0;
	n = i;
	while (cmd->args[++i])
		len += ft_strlen(cmd->args[i]);
	len += i;
	append = (char *)malloc(sizeof(char) * (len + 1));
	if (!append)
		return (NULL);
	len = -1;
	i = n;
	while (cmd->args[++i])
	{
		j = -1;
		while (cmd->args[i][++j])
			append[++len] = cmd->args[i][j];
		append[++len] = ' ';
	}
	append[len] = '\0';
	return (append);
}
