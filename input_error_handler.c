/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:09:27 by artberna          #+#    #+#             */
/*   Updated: 2024/09/24 10:30:57 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_str(t_token *tok)
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
	return (0);
}

static int	handle_redir(t_token *tok)
{
	if (tok->type != TOK_STR && tok->type != TOK_PIPE)
	{
		if (tok->type == TOK_IR && !tok->next)
			return (printf("%s", NL_ERROR), 1);
		else if (tok->type == TOK_IR && tok->next->type == TOK_OR)
			return (printf("%s", OR_ERROR), 1);
		else if (!tok->next || (tok->type == TOK_OR && \
			tok->next->type == TOK_IR))
			return (printf("%s", NL_ERROR), 1);
		else if (tok->type == TOK_IR && tok->next->type == TOK_IR)
			return (printf("%s", IR_ERROR), 1);
		else if (tok->type == TOK_OR && tok->next->type == TOK_OR)
			return (printf("%s", OR_ERROR), 1);
		else if (tok->type == TOK_APP && tok->next->type == TOK_APP)
			return (printf("%s", APP_ERROR), 1);
		else if (tok->type == TOK_HDOC && tok->next->type == TOK_HDOC)
			return (printf("%s", HDOC_ERROR), 1);
	}
	return (0);
}

static int	handle_pipe(t_token *tok)
{
	if (tok->type == TOK_PIPE)
	{
		if (!tok->prev || !tok->next || tok->next->type != TOK_STR)
			return (ft_printf("%s", PIPE_ERROR), 1);
	}
	return (0);
}

int	input_error_handler(t_token **tok)
{
	int	error;

	error = 0;
	while (*tok)
	{
		error += handle_pipe(*tok);
		error += handle_redir(*tok);
		error += handle_str(*tok);
		if (error)
			return (error);
		if ((*tok)->next)
			(*tok) = (*tok)->next;
	}
	return (error);
}
