/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:13:43 by artberna          #+#    #+#             */
/*   Updated: 2024/09/19 16:08:54 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmds	*parser(t_token *tok, char **env)
// {
// 	int		i;
// 	int		j;
// 	t_cmds	*cmd;
// 	t_cmds	*tmp;

// 	cmd = NULL;
// 	i = 0;
// 	j = 0;
// 	while (tok)
// 	{
// 		if (tok->token[0] == '\"' || tok->token[0] == '\'')
// 		{
// 			tok->token = clean_quote(tok->token, tok->token[0]);
// 			if (!tok->token)
// 			{
// 				free_token(tok);
// 				exit_error("clean quote failed");
// 			}
// 		}
// 	}
// 	return (cmd);
