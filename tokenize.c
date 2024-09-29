/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:12:32 by merdal            #+#    #+#             */
/*   Updated: 2024/09/29 16:10:10 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_expand(char *input, int *i, t_env *env)
{
	int		len;
	char	*token;

	len = ft_token_len(input, *i);
	token = ft_handle_dollar(ft_cut(input, *i, len), env);
	*i = *i + len;
	return (token);
}

char	*ft_handle_quotes(char *input, int *i)
{
	int		len;
	int		x;
	char	quote;
	char	*token;

	quote = input[(*i)++];
	len = 0;
	while (input[*i + len] && input[*i + len] != quote)
		len++;
	len = len + 2;
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	token[0] = quote;
	x = 1;
	while (x < len - 1)
	{
		token[x] = input[*i];
		x++;
		(*i)++;
	}
	token[len - 1] = quote;
	token[len] = '\0';
	(*i)++;
	return (token);
}

char	*ft_handle_regular(char *input, int *i)
{
	int		len;
	int		x;
	char	*token;

	len = ft_token_len(input, *i);
	token = malloc(sizeof(char) *(len + 1));
	if (!token)
		return (NULL);
	x = 0;
	while (x < len)
	{
		token[x] = input[*i];
		x++;
		(*i)++;
	}
	token[len] = '\0';
	return (token);
}

char	**ft_create_array(char *input, t_env *env)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (ft_count_tokens(input) + 1));
	if (!array)
		return (NULL);
	while (j < ft_count_tokens(input))
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '$')
			array[j++] = ft_expand(input, &i, env);
		else if (input[i] == '"' || input[i] == '\'')
			array[j++] = ft_handle_quotes(input, &i);
		else
			array[j++] = ft_handle_regular(input, &i);
	}
	array[j] = NULL;
	return (array);
}
