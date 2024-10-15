/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:29:54 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/15 15:38:12 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exec(t_cmds *cmds, t_env *struct_env)
{
	if (is_it_builtins(cmds) == 0 && cmds->g_data->nb_command == 1)
	{
		if (cmds->nb_redir == 0 || is_it_heredoc(cmds) == 0)
			redirection(cmds, struct_env);
	}
	else if (cmds->g_data->nb_command == 1)
		one_command(cmds, struct_env);
	else
	{

		multiple_commands(cmds, struct_env);
	}
}

void	multiple_commands(t_cmds *cmds, t_env *struct_env)
{
	int		fd[2];
	int		infile;
	pid_t	pid;
	t_cmds	*temp;

	infile = STDIN_FILENO;
	temp = cmds;
	//printf("%u\n", temp->redir->type);
	while (temp != NULL)
	{
		if (pipe(fd) == -1 && temp->next != NULL)
			return (ft_error("pipe failed ", temp));
		pid = fork();
		if (pid == -1)
			return (fork_error(temp, fd));
		temp->flag_error = 1;
		if (pid == 0)
		{
			//printf("la\n");
			child_process(temp, infile, fd, struct_env);
		}
		else
			parent_process(fd, &infile, pid);
		temp = temp->next;
	}
	if (is_it_heredoc_2(cmds) == 1)
		unlink("/tmp/HDOC_FILE");
	if (infile != STDIN_FILENO)
		close(infile);
}

void	parent_process(int *fd, int *infile, pid_t pid)
{
	close(fd[1]);
	if (*infile != STDIN_FILENO)
		close(*infile);
	*infile = fd[0];
	waitpid(pid, NULL, 0);
}

void	child_process(t_cmds *temp, int infile, int *fd, t_env *struct_env)
{
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
