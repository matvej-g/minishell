/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:22:46 by mgering           #+#    #+#             */
/*   Updated: 2024/09/23 16:36:03 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(const t_cmd *cmd)
{
	if (0 == ft_strcmp(cmd->args[1], "-n"))
		printf("%s", ft_append_char_struct(cmd, 1));
	else
		printf("%s\n", ft_append_char_struct(cmd, 0));
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
