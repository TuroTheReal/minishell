/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:13:43 by artberna          #+#    #+#             */
/*   Updated: 2024/10/07 16:05:06 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd(t_cmds **head, t_cmds **curr, t_gdata *data)
{
	*head = ft_calloc(sizeof(t_cmds), 1);
	*curr = *head;
	ft_memset(*curr, 0, sizeof(t_cmds));
	(*curr)->cmd = NULL;
	(*curr)->next = NULL;
	(*curr)->prev = NULL;
	(*curr)->redir = NULL;
	(*curr)->hdoc = NULL;
	(*curr)->g_data = data;
}

t_cmds	*parser(t_token *tok, t_gdata *data, char **env)
{
	t_cmds	*head;
	t_cmds	*curr;
	t_token	*tmp;

	head = NULL;
	curr = NULL;
	tmp = tok;
	init_cmd(&head, &curr, data);
	parsenize(curr, tmp, env, data);
	return (head);
}
