/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:02 by merdal            #+#    #+#             */
/*   Updated: 2024/10/13 15:45:23 by mgering          ###   ########.fr       */
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

int	ft_array_len(char **array, int i)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[i + len] && !ft_is_operator(array[i + len]))
		len++;
	return (len);
}

void	ft_fd_heredoc(t_cmd *temp)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
	}
	pid = fork();
	if (pid == 0)
		ft_heredoc_process(temp, pipe_fd[1]);
	else if (pid > 0)
	{
		signal (SIGINT, SIG_IGN);
		wait(NULL);
		init_signal_handler();
		close(pipe_fd[1]);
		temp->input_fd = pipe_fd[0];
	}
	else
		perror("fork heredoc");
}

void	ft_heredoc_process(t_cmd *temp, int pipe_fd)
{
	char	*input;

	signal(SIGINT, child_signal_handler);
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_strcmp(input, temp->next->args[0]) == 0)
		{
			free(input);
			exit(0);
		}
		write(pipe_fd, input, strlen(input));
		write(pipe_fd, "\n", 1);
		free(input);
	}
}
