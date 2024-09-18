/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:38:50 by artberna          #+#    #+#             */
/*   Updated: 2024/09/18 17:05:33 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_close_quote(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	get_token_str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += get_close_quote(&s[i], '\'');
		else if (s[i] == '\"')
			i += get_close_quote(&s[i], '\"');
		else if (ft_strrchr(IS_TOKEN, s[i]) || (s[i] == ' ' || s[i] == '\t'))
			break ;
		i++;
	}
	return (i);
}

static int	get_token_len(char *s, t_token_type type)
{
	int	len;

	len = 0;
	if (type == TOK_APP_REDIR || type == TOK_HEREDOC)
		len = 2;
	else if (type == TOK_I_REDIR || type == TOK_O_REDIR || type == TOK_PIPE)
		len = 1;
	else if (type == TOK_STR)
		len = get_token_str_len(s);
	return (len);
}

static t_token_type	get_token_type(char *s)
{
	if (s[0] == '|')
		return (TOK_PIPE);
	else if (s[0] == '<')
	{
		if (s[1] == '<')
			return (TOK_HEREDOC);
		return (TOK_I_REDIR);
	}
	else if (s[0] == '>')
	{
		if (s[1] == '>')
			return (TOK_APP_REDIR);
		return (TOK_O_REDIR);
	}
	return (TOK_STR);
}

t_token	*tokenize(char *s)
{
	int				len;
	t_token			*node;
	t_token_type	type;

	len = 0;
	node = NULL;
	type = get_token_type(s);
	len = get_token_len(s, type);
	node = create_token(s, len, type);
	return (node);
}
