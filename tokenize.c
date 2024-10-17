/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:12:32 by merdal            #+#    #+#             */
/*   Updated: 2024/10/17 15:01:38 by mgering          ###   ########.fr       */
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
	char	*cut_token;

	len = ft_token_len(input, *i);
	cut_token = ft_cut(input, *i, len);
	token = ft_handle_dollar(cut_token, env);
	*i = *i + len;
	free(cut_token);
	return (token);
}

char	*ft_handle_quotes(char *input, int *i, t_env *env)
{
	int		len;
	int		x;
	char	quote;
	char	*token;

	while (input[*i] == '\'' || input[*i] == '\"')
		quote = input[(*i)++];
	len = 0;
	while (input[*i + len] && input[*i + len] != quote)
		len++;
	token = malloc(sizeof(char) * (len + 1));
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
	(*i)++;
	if (token[0] == '$' && quote == '\"')
		return (ft_handle_dollar(token, env));
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
		else if (input[i] == '\"' || input[i] == '\'')
			array[j++] = ft_handle_quotes(input, &i, env);
		else
			array[j++] = ft_handle_regular(input, &i);
	}
	array[j] = NULL;
	return (array);
}
