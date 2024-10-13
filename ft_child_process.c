/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:05:12 by mgering           #+#    #+#             */
/*   Updated: 2024/10/12 14:05:36 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(const t_cmd *cmd, t_env *env)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	redirect_fd(cmd);
	check_executable(cmd, env);
	exit(EXIT_SUCCESS);
}

void	wait_child_process(const t_cmd *cmd, t_env *env, int pid)
{
	int	status;

	signal (SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->exit_status = 128 + WTERMSIG(status);
	init_signal_handler();
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}
