/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:51:08 by merdal            #+#    #+#             */
/*   Updated: 2024/10/11 16:12:59 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_fix_struct(t_cmd *cmd_head)
{
	t_cmd	*current;
	t_cmd	*delete;

	current = cmd_head;
	if (current->operator && ft_strcmp(current->operator, "<") == 0
		&& current->next->operator
		&& ft_strcmp(current->next->operator, "|") == 0)
	{
		current->output_fd = current->next->output_fd;
		delete = current->next;
		current->next = current->next->next;
		delete->next = NULL;
		free_cmd(delete);
	}
	else if (current->operator && ft_strcmp(current->operator, "<<") == 0
		&& current->next->operator)
	{
		current->output_fd = current->next->output_fd;
		delete = current->next;
		current->next = current->next->next;
		delete->next = NULL;
		free_cmd(delete);
	}
	else if (current->operator && current->next && !current->next->operator
		&& ft_strcmp(current->operator, "|") != 0)
	{
		delete = current->next;
		current->next = NULL;
		free_cmd(delete);
	}
	return (cmd_head);
}

t_cmd	*ft_set_fds(t_cmd *temp)
{
	t_cmd	*new_head;

	new_head = temp;
	while (temp->next)
	{
		if (ft_strcmp(temp->operator, ">") == 0)
			ft_fd_rdr(temp);
		else if (ft_strcmp(temp->operator, ">>") == 0)
			ft_fd_rdrapp(temp);
		else if (ft_strcmp(temp->operator, "<") == 0)
			ft_fd_rdr2(temp);
		else if (ft_strcmp(temp->operator, "<<") == 0)
			ft_fd_heredoc(temp);
		else if (ft_strcmp(temp->operator, "|") == 0)
			ft_pipe(temp);
		temp = temp->next;
	}
	if (1 == g_signal_received)
	{
		free_cmd(new_head);
		return (NULL);
	}
	new_head = ft_fix_struct(new_head);
	return (new_head);
}
