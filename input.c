/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:54:14 by merdal            #+#    #+#             */
/*   Updated: 2024/10/17 17:07:47 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_operator(char *input, int *i, t_env *env)
{
	char	**operators;
	int		j;
	int		op_len;

	operators = ft_init_op();
	j = 0;
	while (operators[j] != NULL)
	{
		op_len = ft_strlen(operators[j]);
		if (ft_strncmp(&input[*i], operators[j], op_len) == 0)
		{
			*i += op_len;
			while (input[*i] != '\0' && ft_isspace((unsigned char)input[*i]))
				(*i)++;
			if (input[*i] == '\0' || ft_isspace((unsigned char)input[*i]))
				ft_return_and_exit("Error: syntax error operator", 1, env);
			free(operators);
			return (1);
		}
		j++;
	}
	free(operators);
	return (0);
}

int	ft_check_op_end(char *input, t_env *env)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (ft_check_operator(input, &i, env) == 1)
			continue ;
		i++;
	}
	return (0);
}

char	*ft_get_input(t_env *env)
{
	char	*input;

	input = readline(" -- minishell -- $ ");
	if (input == NULL)
	{
		free_env_lst(env);
		printf("exit\n");
		exit (0);
	}
	else if (g_signal_received == 130)
	{
		env->exit_status = 1;
		return (input);
	}
	return (input);
}

int	ft_check_quotes(char *input)
{
	char	quote_type;
	int		i;

	quote_type = 0;
	i = 0;
	while (input[i] && !quote_type)
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote_type = input[i];
		i++;
	}
	while (input[i] && quote_type)
	{
		if (input[i] && input[i] == quote_type)
			quote_type = 0;
		i++;
	}
	if (input[i])
		return (ft_check_quotes(&input[i]));
	else if (!quote_type)
		return (0);
	else
		return (1);
}

int	ft_check_input(char *input, t_env *env)
{
	if (input[0] == '\0')
	{
		ft_return_and_exit(NULL, 0, env);
		return (1);
	}
	if (ft_check_quotes(input))
	{
		ft_return_and_exit("Error: unclosed quotes", 2, env);
		return (1);
	}
	if (env->exec_flag == 0)
		ft_check_syntax(input, env);
	if (env->exec_flag == 0)
		ft_check_op_end(input, env);
	if (env->exec_flag == 0)
		ft_check_op(input, env);
	if (env->exec_flag == 0)
		ft_check_syntax_op(input, env);
	return (0);
}
