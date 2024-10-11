/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:49:21 by artberna          #+#    #+#             */
/*   Updated: 2024/10/11 16:44:36 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_cmds *cmd, t_token **tok)
{
	t_token		*new_tok;
	t_token_type	type;

	type = (*tok)->type;
	while ((*tok)->type == TOK_SPC)
		(*tok) = (*tok)->next;
	// if (!(*tok) || !is_cmd((*tok)->type))
	// 	return ;
	new_tok = create_token((*tok)->token, ft_strlen((*tok)->token), type);
	if (!new_tok)
		exit_error("create_token failed");
	cmd->nb_redir++;
	if (cmd->redir)
		add_token(&(cmd->redir), new_tok);
	else
		cmd->redir = new_tok;
	(*tok) = (*tok)->next;
}
