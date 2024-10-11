/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:09:27 by artberna          #+#    #+#             */
/*   Updated: 2024/10/11 15:07:13 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_error(t_token *tok)
{
	if (tok->type == TOK_STR || tok->type == TOK_S_Q || tok->type == TOK_D_Q)
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

static int	redir_error(t_token *tok)
{
	if (tok->type != TOK_STR && tok->type != TOK_PIPE \
		&& tok->type != TOK_S_Q && tok->type != TOK_D_Q)
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

static int	pipe_error(t_token *tok)
{
	if (tok->type == TOK_PIPE)
	{
		if (!tok->prev || !tok->next)
			return (ft_printf("%s", PIPE_ERROR), 1);
	}
	return (0);
}

int	error_handler(t_token **tok, t_gdata *data)
{
	int		error;
	t_token	*tmp;

	error = 0;
	tmp = *tok;
	while (tmp)
	{
		error += pipe_error(tmp);
		error += redir_error(tmp);
		error += str_error(tmp);
		if (error)
		{
			free_token(*tok);
			free(data->input);
			rl_on_new_line();
			return (error);
		}
		if ((tmp)->next)
			(tmp) = (tmp)->next;
		else
			return (error);
	}
	return (error);
}
