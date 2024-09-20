/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:09:27 by artberna          #+#    #+#             */
/*   Updated: 2024/09/20 11:21:21 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_str(t_token *tok)
{
	while (tok)
	{
		if (tok->type == TOK_STR)
		{
			if (tok->token[0] == '!' && tok->token[1] == '\0')
				return (1);
			if (tok->token[0] == ':' && tok->token[1] == '\0')
				return (1);
			if (tok->token[0] == '#')
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}

static int	handle_pipe(t_token *tok)
{
	while (tok)
	{
		if (tok->type == TOK_PIPE)
		{
			if (!tok->next || tok->next->type == TOK_PIPE)
				return (ft_printf("%s", S_PIPE_ERROR), 1);
			else if (tok->next->type != TOK_STR)
			{
				if (tok->next->type == TOK_PIPE)
					return (ft_printf("%s", D_PIPE_ERROR), 1);
			}
		}
		if (tok->next)
			tok = tok->next;
		else
			return (0);
	}
	return (0);
}

int	input_error_handler(t_token **tok)
{
	int	error;

	error = 0;
	error += handle_str(*tok);
	error += handle_pipe(*tok);
	// error += handle_i_redir_app(tok);
	// error += handle_o_redir_heredoc(tok);
	return (error);
}
