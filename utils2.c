/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:57:29 by merdal            #+#    #+#             */
/*   Updated: 2024/09/29 15:56:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_rdr(t_cmd *temp)
{
	temp->output_fd = open(temp->next->args[0],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp->output_fd == -1)
	{
		perror("open");
	}
}

void	ft_fd_rdrapp(t_cmd *temp)
{
	temp->output_fd = open(temp->next->args[0],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp->output_fd == -1)
	{
		perror("open");
	}
}

void	ft_fd_rdr2(t_cmd *temp)
{
	temp->input_fd = open(temp->next->args[0], O_RDONLY);
	if (temp->input_fd == -1)
	{
		perror("open");
	}
}

void	ft_fd_heredoc(t_cmd *temp)
{
	int		pipe_fd[2];
	char	*input;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
	}
	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strcmp(input, temp->next->args[0]) == 0)
		{
			free(input);
			break ;
		}
		write(pipe_fd[1], input, strlen(input));
		write(pipe_fd[1], "\n", 1);
		free(input);
	}
	close(pipe_fd[1]);
	temp->input_fd = pipe_fd[0];
}

void	ft_pipe(t_cmd *temp)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
	}
	temp->output_fd = pipe_fd[0];
	if (temp->output_fd == -1)
	{
		perror("pipe");
	}
	if (temp->next != NULL)
	{
		temp->next->input_fd = pipe_fd[1];
		if (temp->next->input_fd == -1)
		{
			perror("pipe");
		}
	}
}
