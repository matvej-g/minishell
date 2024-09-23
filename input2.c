/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:54 by merdal            #+#    #+#             */
/*   Updated: 2024/07/14 17:38:54 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax(char *input, t_env *env)
{
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
	{
		ft_return_and_exit("Error: syntax error pipes", 1, env);
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '<')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>' && input[ft_strlen(input) - 2] == '>')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	return (0);
}

int	ft_check_op(char *input, t_env *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if (((input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '|' && input[i + 1] == '|')) && quote == 0)
		{
			ft_return_and_exit("Error: syntax error", 1, env);
			return (1);
		}
		else if ((input[i] == '{' || input[i] =='}' || input[i] == '[' || input[i] == ']'
					|| input[i] == '(' || input[i] == ')' || input[i] == '&'
					|| input[i] == ';' || input[i] == '*') && quote == 0)
		{
			ft_return_and_exit("Error: syntax error", 1, env);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_syntax_op(char *input, t_env *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while(input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && quote == 0)
		{
			if (input[i] == input[i + 1])
				i = i + 2;
			else
				i++;
			if (input[i] == ' ')
			{
				while (input[i] == ' ')
					i++;
				if (input[i] == '<' || input[i] == '>' || input[i] == '|')
				{
					ft_return_and_exit("Error: syntax error", 1, env);
					return (1);
				}
			}
			if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			{
				ft_return_and_exit("Error: syntax error", 1, env);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
