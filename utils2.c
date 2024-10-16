/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:57:29 by merdal            #+#    #+#             */
/*   Updated: 2024/10/13 15:34:58 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_rdr(t_cmd *temp)
{
	temp->output_fd = open(temp->next->args[0],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp->output_fd == -1)
	{
		g_signal_received = 1;
		perror("open");
	}
}

void	ft_fd_rdrapp(t_cmd *temp)
{
	temp->output_fd = open(temp->next->args[0],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp->output_fd == -1)
	{
		g_signal_received = 1;
		perror("open");
	}
}

void	ft_fd_rdr2(t_cmd *temp)
{
	temp->input_fd = open(temp->next->args[0], O_RDONLY);
	if (temp->input_fd == -1)
	{
		g_signal_received = 1;
		perror("open");
	}
}

void	ft_pipe(t_cmd *temp)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
	}
	temp->output_fd = pipe_fd[1];
	if (temp->output_fd == -1)
	{
		perror("pipe");
	}
	if (temp->next != NULL)
	{
		temp->next->input_fd = pipe_fd[0];
		if (temp->next->input_fd == -1)
		{
			perror("pipe");
		}
	}
}
