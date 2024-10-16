/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:06:05 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 15:08:09 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe(t_cmd **cmd, t_env *env)
{
	t_cmd		*tmp_cmd;
	pid_t		*pid;
	int			num_cmds;

	num_cmds = 1;
	tmp_cmd = *cmd;
	while (tmp_cmd->operator && 0 == ft_strcmp(tmp_cmd->operator, "|"))
	{
		num_cmds++;
		tmp_cmd = tmp_cmd->next;
	}
	pid = malloc(num_cmds * sizeof(pid_t));
	if (!pid)
	{
		perror("malloc pid");
		exit(EXIT_FAILURE);
	}
	fork_child_processes(*cmd, env, pid, num_cmds);
	close_fds_in_parent(*cmd, num_cmds);
	wait_for_children(*cmd, env, pid, num_cmds);
	*cmd = tmp_cmd;
	free(pid);
}

void	fork_child_processes(t_cmd *cmd, t_env *env, pid_t *pid, int num_cmds)
{
	t_cmd	*tmp_cmd;
	int		i;

	tmp_cmd = cmd;
	i = -1;
	while (++i < num_cmds)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(tmp_cmd, env);
		else if (pid[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		tmp_cmd = tmp_cmd->next;
	}
}

void	close_fds_in_parent(t_cmd *cmd, int num_cmds)
{
	t_cmd	*tmp_cmd;
	int		i;

	tmp_cmd = cmd;
	i = -1;
	while (++i < num_cmds)
	{
		if (tmp_cmd->input_fd != STDIN_FILENO)
		{
			close(tmp_cmd->input_fd);
			tmp_cmd->input_fd = -1;
		}
		if (tmp_cmd->output_fd != STDOUT_FILENO)
		{
			close(tmp_cmd->output_fd);
			tmp_cmd->output_fd = -1;
		}
		tmp_cmd = tmp_cmd->next;
	}
}

void	wait_for_children(t_cmd *cmd, t_env *env, pid_t *pid, int num_cmds)
{
	t_cmd	*tmp_cmd;
	int		i;

	tmp_cmd = cmd;
	i = -1;
	while (++i < num_cmds)
	{
		wait_child_process(tmp_cmd, env, pid[i]);
		if (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
	}
}
