/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:11:55 by merdal            #+#    #+#             */
/*   Updated: 2024/09/29 15:57:57 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

t_cmd	*ft_new_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->operator = NULL;
	node->args = NULL;
	node->input_fd = STDIN_FILENO;
	node->output_fd = STDOUT_FILENO;
	node->next = NULL;
	return (node);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] && !ft_is_operator(array[len]))
		len++;
	return (len);
}

void	ft_populate_args(t_cmd *temp, char **array, int *i)
{
	int	arg_index;

	arg_index = 0;
	temp->args = (char **)malloc(sizeof(char *) * (ft_array_len(array) + 1));
	while (array[*i] && !ft_is_operator(array[*i]))
	{
		temp->args[arg_index++] = array[*i];
		(*i)++;
	}
	temp->args[arg_index] = NULL;
}

void	ft_handle_operator(t_cmd *temp, char **array, int *i)
{
	if (array[*i] && ft_is_operator(array[*i]))
	{
		temp->operator = array[*i];
		(*i)++;
		if (ft_strcmp(temp->operator, "<<") == 0 && array[*i])
			temp->heredoc_delimiter = array[*i];
	}
	else
		temp->operator = NULL;
}

t_cmd	*ft_create_next_node(t_cmd *temp, char **array, int *i)
{
	if (array[*i] != NULL)
	{
		temp->next = ft_new_node();
		return (temp->next);
	}
	return (temp);
}

t_cmd	*ft_parser(char *input, t_env *env)
{
	int		i;
	char	**array;
	t_cmd	*cmd_head;
	t_cmd	*temp;

	i = 0;
	if (!input)
		return (NULL);
	array = ft_create_array(input, env);
	if (!array)
		return (NULL);
	cmd_head = ft_new_node();
	temp = cmd_head;
	while (array[i] != NULL)
	{
		ft_populate_args(temp, array, &i);
		ft_handle_operator(temp, array, &i);
		temp = ft_create_next_node(temp, array, &i);
	}
	temp->next = NULL;
	return (ft_set_fds(cmd_head));
}
