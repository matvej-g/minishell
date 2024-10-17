/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:54 by merdal            #+#    #+#             */
/*   Updated: 2024/10/16 17:41:33 by mgering          ###   ########.fr       */
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
	if (input[0] == '>' || input[ft_strlen(input) - 1] == '>')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	if (input[0] == '<' || input[ft_strlen(input) - 1] == '<')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>'
		&& input[ft_strlen(input) - 2] == '>')
	{
		ft_return_and_exit("Error: syntax error redirection", 1, env);
		return (1);
	}
	return (0);
}

int	ft_is_invalid(char c1, char c2)
{
	return ((c1 == '>' && c2 == '<') || (c1 == '<' && c2 == '>')
		|| (c1 == '|' && c2 == '|')
		|| c1 == '{' || c1 == '}' || c1 == '[' || c1 == ']'
		||c1 == '(' || c1 == ')' || c1 == '&' || c1 == ';' || c1 == '*');
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
		if (ft_is_invalid(input[i], input[i + 1] && quote == 0))
		{
			ft_return_and_exit("Error: syntax error", 1, env);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_operator_and_space(char *input, int *i, t_env *env)
{
	if (input[*i] == input[*i + 1])
		*i += 2;
	else
		(*i)++;
	if (input[*i] == ' ')
	{
		while (input[*i] == ' ')
			(*i)++;
		if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
		{
			ft_return_and_exit("Error: syntax error", 1, env);
			return (1);
		}
	}
	return (0);
}

int	ft_check_syntax_op(char *input, t_env *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if ((input[i] == '<' || input[i] == '>'
				|| input[i] == '|') && quote == 0)
		{
			if (ft_check_operator_and_space(input, &i, env))
				return (1);
			if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			{
				ft_return_and_exit("Error: syntax error", 2, env);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
