/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:22:46 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 17:47:21 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	char	*str_struct;

	if (!cmd->args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_is_n(cmd->args[1]) == 1)
	{
		if (!cmd->args[2])
			return ;
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

char	*ft_append_char_struct(t_cmd *cmd, int i)
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
