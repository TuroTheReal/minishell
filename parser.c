/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:13:43 by artberna          #+#    #+#             */
/*   Updated: 2024/09/25 14:41:20 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env(char *token, char	**env)
{
}

static void	expand_env(t_token *tok, char **env)
{
}

static void	flag_quote(t_token *tok)
{
}

t_cmds	*parser(t_token *tok, char **env)
{
	t_cmds	*cmd;

	cmd = NULL;
	while (tok)
	{
		// rmv_quote(tok);
		// expand_env(tok, env);
		// check_null_n_remove(tok);
		// join_cmd(cmd, tok);
		if (tok->next)
			tok = tok->next;
		else
			break ;
	}
	return (cmd);
}
