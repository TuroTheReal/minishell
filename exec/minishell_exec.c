/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:29:54 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/23 17:28:41 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exec(t_cmds *cmds, t_env *struct_env)
{
	pid_t	*pid;

	if (is_it_builtins(cmds) == 0 && cmds->g_data->nb_command == 1
		&& is_it_heredoc(cmds) == 0)
		redirection(cmds, struct_env);
	else if (cmds->g_data->nb_command == 1)
		one_command(cmds, struct_env);
	else
	{
		pid = ft_calloc(cmds->g_data->nb_command, sizeof(pid_t));
		multiple_commands(cmds, struct_env, -1, pid);
	}
}

void	multiple_commands(t_cmds *cmds, t_env *struct_env, int i, pid_t *pid)
{
	int		fd[2];
	int		infile;
	t_cmds	*temp;

	infile = STDIN_FILENO;
	temp = cmds;
	while (temp != NULL)
	{
		if (pipe(fd) == -1 && temp->next != NULL)
			return (ft_error("pipe failed ", temp));
		pid[++i] = fork();
		if (pid[i] == -1)
			return (fork_error(temp, fd));
		temp->flag_error = 1;
		if (pid[i] == 0)
			child_process(temp, infile, fd, struct_env);
		else
		{
			if (is_it_heredoc(temp) == 1)
				waitpid(pid[i], NULL, 0); // a remplacer par &status et transmettre a exit code
			parent_process(fd, &infile);
		}
		temp = temp->next;
	}
	all_waitpid(cmds, pid, &infile);
}

void	all_waitpid(t_cmds *cmds, pid_t *pid, int *infile)
{
	int		i;
	t_cmds	*temp;
	int		count;

	count = cmds->g_data->nb_command;
	i = 0;
	temp = cmds;
	while (count > 0)
	{
		if (is_it_heredoc(temp) == 0)
			waitpid(pid[i], NULL, 0); // a remplacer par &status et transmettre a exit code
		count--;
		i++;
		temp = temp->next;
	}
	free(pid);
	if (is_it_heredoc_2(cmds) == 1)
		unlink("/tmp/HDOC_FILE");
	if (*infile != STDIN_FILENO)
		close(*infile);
}

void	parent_process(int *fd, int *infile)
{
	// signal(SIGINT, SIG_IGN);
	// printf("PARENT MTP CMD\n"); //debug
	close(fd[1]);
	if (*infile != STDIN_FILENO)
		close(*infile);
	*infile = fd[0];
}

void	child_process(t_cmds *temp, int infile, int *fd, t_env *struct_env)
{
	init_signal(2, NULL);
	printf("CHILD MTP CMD\n"); //debug
	if (is_it_heredoc(temp) == 1)
		create_hdoc_file(temp);
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (temp->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close(fd[0]);
	redirection(temp, struct_env);
	exit(0);
}
