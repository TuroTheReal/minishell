/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsindres <dsindres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:54:13 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/21 18:03:39 by dsindres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, t_cmds *cmds)
{
	if (errno == ENOENT)
		perror(str);
	else
		fprintf(stderr, "%s: command not found\n", cmds->cmd[0]);
	if (cmds->flag_error == 1)
		exit (EXIT_FAILURE);
}

void	fork_error(t_cmds *temp, int *fd)
{
	if (temp->next != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	ft_error("fork failed ", temp);
}

int	is_it_heredoc(t_cmds *cmds)
{
	t_token	*temp;

	temp = cmds->redir;
	while (temp != NULL)
	{
		if (temp->type == TOK_HDOC)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	is_it_heredoc_2(t_cmds *cmds)
{
	t_cmds	*temp;
	t_token	*temp_2;

	temp = cmds;
	temp_2 = temp->redir;
	while (temp != NULL)
	{
		while (temp_2 != NULL)
		{
			if (temp_2->type == TOK_HDOC)
				return (1);
			temp_2 = temp_2->next;
		}
		temp = temp->next;
	}
	return (0);
}

void	file_fd_value(t_token *in, int *file_fd)
{
	if (in->type == TOK_HDOC)
		*file_fd = open("/tmp/HDOC_FILE", O_RDONLY, 0777);
	else
		*file_fd = open(in->token, O_RDONLY, 0777);
}
