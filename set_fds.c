/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:51:08 by merdal            #+#    #+#             */
/*   Updated: 2024/09/29 15:55:14 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (new_head);
}
