/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:11:55 by merdal            #+#    #+#             */
/*   Updated: 2024/09/23 15:31:24 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 ||
		ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 ||
		ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

t_cmd	*ft_new_node(void)
{
	t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);

	node->operator = NULL;
	node->args = NULL;
	node->input_fd = 0;
	node->output_fd = 1;
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

t_cmd	*ft_parser(char *input, t_env *env)
{
	int		i;
	int		arg_index;
	char	**array;
	t_cmd	*cmd_head;
	t_cmd	*temp;

	i = 0;
	arg_index = 0;
	array = ft_create_array(input, env);
	if (!array)
		return (NULL);
	temp = ft_new_node();
	cmd_head = temp;
	while (array[i] != NULL)
	{
		temp->args = (char **)malloc(sizeof(char *) * (ft_array_len(array) + 1));
		arg_index = 0;
		while (array[i] && !ft_is_operator(array[i]))
		{
			temp->args[arg_index] = array[i];
			i++;
			arg_index++;
		}
		temp->args[arg_index] = NULL;
		if (array[i] && ft_is_operator(array[i]))
		{
			temp->operator = array[i];
			i++;
		}
		else
			temp->operator = NULL;
		if (array[i] != NULL)
		{
			temp->next = ft_new_node();
			temp = temp->next;
		}
	}
	temp->next = NULL;
	temp = ft_set_fds(cmd_head);
	return (temp);
}
