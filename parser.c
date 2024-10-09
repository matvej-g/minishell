/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:11:55 by merdal            #+#    #+#             */
/*   Updated: 2024/10/08 14:46:58 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	node->heredoc_delimiter = NULL;
	node->next = NULL;
	return (node);
}

void	ft_populate_args(t_cmd *temp, char **array, int *i)
{
	int	arg_index;
	int	len;

	arg_index = 0;
	len = ft_array_len(array, *i);
	temp->args = (char **)malloc(sizeof(char *) * (len + 1));
	while (array[*i] && !ft_is_operator(array[*i]))
	{
		temp->args[arg_index++] = ft_strdup(array[*i]);
		(*i)++;
	}
	temp->args[arg_index] = NULL;
}

void	ft_handle_operator(t_cmd *temp, char **array, int *i)
{
	if (array[*i] && ft_is_operator(array[*i]))
	{
		temp->operator = ft_strdup(array[*i]);
		(*i)++;
		if (ft_strcmp(temp->operator, "<<") == 0 && array[*i])
			temp->heredoc_delimiter = ft_strdup(array[*i]);
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
	array = NULL;
	cmd_head = ft_new_node();
	temp = cmd_head;
	if (env->exec_flag == 0)
	{
		array = ft_create_array(input, env);
		free(input);
		if (!array)
			return (NULL);
		while (array[i] != NULL)
		{
			ft_populate_args(temp, array, &i);
			ft_handle_operator(temp, array, &i);
			temp = ft_create_next_node(temp, array, &i);
		}
		temp->next = NULL;
	}
	ft_free_split(array);
	return (ft_set_fds(cmd_head));
}
