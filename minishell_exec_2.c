/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:15:00 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/18 16:34:26 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_command(t_cmds *cmds, t_env *struct_env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		ft_error("pipe failed ", cmds);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		fork_error(cmds, fd);
		return ;
	}
	cmds->flag_error = 1;
	if (pid == 0)
		child_process_one_command(cmds, struct_env);
	if (pid > 0) //ajout Arthur signaux
	{
		signal(SIGINT, SIG_IGN);
		printf("PARENT SGL CMD\n"); //debug
	}
	close (fd[1]);
	close (fd[0]);
	waitpid(pid, NULL, 0);
	if (is_it_heredoc(cmds) == 1)
		unlink("/tmp/HDOC_FILE");
	return ;
}

void	child_process_one_command(t_cmds *cmds, t_env *struct_env)
{
	init_signal(2);
	printf("CHILD SGL CMD\n"); //debug
	if (is_it_heredoc(cmds) == 1)
		create_hdoc_file(cmds);
	redirection(cmds, struct_env);
	exit(0);
}

void	redirection(t_cmds *cmds, t_env *struct_env)
{
	int	in_flag;
	int	out_flag;

	if (cmds->nb_redir == 0)
		execution(cmds, struct_env);
	else
	{
		in_flag = change_in_stdin(cmds);
		out_flag = change_in_stdout(cmds);
		execution(cmds, struct_env);
		if (in_flag == 0)
			change_out_stdin(cmds);
		if (out_flag == 0)
			change_out_stdout(cmds);
	}
}

void	create_hdoc_file(t_cmds *cmds)
{
	int		fd;
	char	*line;
	t_token	*temp_tok;

	init_signal(1);
	line = NULL;
	temp_tok = cmds->redir;
	while (temp_tok != NULL)
	{
		if (temp_tok->type == TOK_HDOC)
		{
			fd = open("/tmp/HDOC_FILE", O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (fd < 0)
				ft_error("Failed to open HDOC_FILE", cmds);
			while (1)
			{
				if (input_heredoc(temp_tok, line, fd) == 0)
					break ;
			}
			close (fd);
		}
		temp_tok = temp_tok->next;
	}
}

int	input_heredoc(t_token *temp_tok, char *line, int fd)
{
	line = readline("> ");
	if (line == NULL || ft_strncmp(line, temp_tok->token,
			(ft_strlen(line) + ft_strlen(temp_tok->token))) == 0)
	{
		free(line);
		return (0);
	}
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
	return (1);
}
