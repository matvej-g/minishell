/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:56:22 by merdal            #+#    #+#             */
/*   Updated: 2024/10/18 20:01:48 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_return_and_exit(char *error, int exit_status, t_env *env)
{
	if (error == NULL)
		return ;
	else
		printf("%s\n", error);
	env->exec_flag = 1;
	env->exit_status = exit_status;
}

int	ft_skip_quotes(char *input, int *i)
{
	char	quotes;

	quotes = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quotes)
		(*i)++;
	if (input[*i] == quotes)
		(*i)++;
	return (1);
}

char	*ft_cut(char *input, int i, int len)
{
	char	*cut;
	int		j;

	j = 0;
	cut = malloc(sizeof(char) * len + 1);
	if (!cut)
		return (NULL);
	while (input[i] != ' ' && input[i])
	{
		cut[j] = input[i];
		i++;
		j++;
	}
	cut[j] = '\0';
	return (cut);
}

int	ft_token_len(char *input, int i)
{
	size_t	len;

	len = 0;
	if (input[i] == '|' || input[i] == '&' || input[i] == ';'
		|| input[i] == '>' || input[i] == '<')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (2);
		if (input[i] == '<' && input[i + 1] == '<')
			return (2);
		return (1);
	}
	while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '&'
		&& input[i] != ';' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '\"' || input[i] == '\'')
			ft_skip_quotes(input, &i);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
