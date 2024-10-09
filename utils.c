/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:20:50 by merdal            #+#    #+#             */
/*   Updated: 2024/10/07 12:01:15 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '>' || c == '<');
}

int	handle_quotes_state(char **input, int quotes)
{
	if ((**input == '"' || **input == '\'') && **input == *(*input + 1))
		(*input)++;
	else if (**input == '"' || **input == '\'')
		quotes = !quotes;
	return (quotes);
}

int	count_meta_operator(char **input)
{
	int	count;

	count = 0;
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
			(*input)++;
		count++;
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
			(*input)++;
		count++;
	}
	else if (is_meta_operator(**input))
		count++;
	return (count);
}

void	handle_token_flags(char c, int *flag, int *count, int quotes)
{
	if (!is_meta_operator(c) && c != ' ' && !*flag && !quotes)
	{
		*flag = 1;
		(*count)++;
	}
	else if (c == ' ' || is_meta_operator(c))
		*flag = 0;
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
		quotes = handle_quotes_state(&input, quotes);
		count += count_meta_operator(&input);
		handle_token_flags(*input, &flag, &count, quotes);
		input++;
	}
	return (count);
}
