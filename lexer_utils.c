/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:34:48 by artberna          #+#    #+#             */
/*   Updated: 2024/09/19 16:49:06 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tok) // debug
{
	while (tok)
	{
		printf("token node n= %d, input = %s, type = %u\n", tok->index, tok->token, tok->type);
		if (!tok->next)
			break ;
		tok = tok->next;
	}
}

void	free_token(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

t_token	*create_token(const char *s, int len, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		exit_error("malloc token structure failed");
	node->type = type;
	node->index = 0;
	node->token = ft_strndup(s, len);
	if (!node->token)
	{
		free(node);
		exit_error("strdup input token failed");
	}
	node->next = NULL;
	return (node);
}

void	add_token(t_token **tok, t_token *new_node)
{
	t_token	*tmp;

	if (!new_node)
		return ;
	if (!*tok || !tok)
		*tok = new_node;
	else
	{
		tmp = *tok;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}
