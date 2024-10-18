/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:05:12 by mgering           #+#    #+#             */
/*   Updated: 2024/10/18 20:13:15 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, t_env *env)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	redirect_fd(cmd);
	close_unused_fds_in_child(cmd);
	check_executable(cmd, env);
	exit(EXIT_SUCCESS);
}

void	wait_child_process(t_cmd *cmd, t_env *env, int pid)
{
	int	status;

	signal (SIGINT, SIG_IGN);
	if (cmd->input_fd >= 0 && cmd->input_fd != STDIN_FILENO)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->exit_status = 128 + WTERMSIG(status);
	init_signal_handler();
}

void	check_executable(t_cmd *cmd, t_env *env)
{
	if (0 == ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (0 == ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (0 == ft_strcmp(cmd->args[0], "PWD"))
		ft_pwd();
	else if (0 == ft_strcmp(cmd->args[0], "env"))
		ft_env(env);
	else if (0 == ft_strcmp(cmd->args[0], "clear"))
		ft_clear();
	else
		ft_exe(cmd, env);
}

void	close_unused_fds_in_child(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->prev)
	{
		tmp = tmp->prev;
	}
	while (tmp)
	{
		if (tmp != cmd)
		{
			if (tmp->input_fd != STDIN_FILENO && tmp->input_fd >= 0)
			{
				close(tmp->input_fd);
				tmp->input_fd = -1;
			}
			if (tmp->output_fd != STDOUT_FILENO && tmp->output_fd >= 0)
			{
				close(tmp->output_fd);
				tmp->output_fd = -1;
			}
		}
		tmp = tmp->next;
	}
}

void	redirect_fd(t_cmd *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
}
