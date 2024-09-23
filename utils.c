/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:20:50 by merdal            #+#    #+#             */
/*   Updated: 2024/09/23 15:23:10 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_return_and_exit(char *error, int exit_status, t_env *env)
{
	printf("%s\n", error);
	env->exit_status = exit_status;
}

int	ft_count_tokens(char *input)
{
	int	count;
	int	flag;
	int	quotes;

	count = 0;
	flag = 0;
	quotes = 0;
	while (*input)
	{
		if (*input == '|' || *input == '&' || *input == ';')
			count += !quotes;
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
				input++;
			count += !quotes;
		}
		else if (*input == '<')
		{
			if (*(input + 1) == '<')
				input++;
			count += !quotes;
		}
		if ((*input == '"' || *input == '\'') && *input == *(input + 1))
			input++;
		else if (*input == '"' || *input == '\'')
			quotes = !quotes;
		if (*input != ' ' && *input != '|' && *input != '&' && *input != ';'
			&& *input != '>' && *input != '<' && !flag && !quotes)
		{
			flag = 1;
			count++;
		}
		else if (*input == ' ' || *input == '|' || *input == '&'
			|| *input == ';' || *input == '>' || *input == '<')
			flag = 0;
		input++;
	}
	return (count);
}

int	ft_token_len(char *input, int i)
{
	size_t	len;
	char	quotes;

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
		{
			quotes = input[i++];
			while (input[i] && input[i] != quotes)
				i++;
			if (input[i] == quotes)
				i++;
		}
		else
			i++;
		len++;
	}
	return (len);
}
