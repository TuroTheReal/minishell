/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:46:15 by artberna          #+#    #+#             */
/*   Updated: 2024/09/25 14:24:21 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote(char *s)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s_quote++;
		if (s[i] == '\"')
			d_quote++;
		i++;
	}
	if (d_quote % 2 != 0 || s_quote % 2 != 0)
		return (printf("%s", QUOTE_ERROR), 1);
	return (0);
}

t_token	*lexer(t_gdata *data)
{
	int		i;
	int		j;
	t_token	*tok;
	t_token	*tmp;

	tok = NULL;
	i = 0;
	j = 0;
	if (handle_quote(data->input))
		return (tok);
	while (data->input[i])
	{
		if (data->input[i] != ' ' && data->input[i] != '\t')
		{
			tmp = tokenize(&data->input[i]);
			if (!tmp)
				return (free_token(tok), free(data->input), NULL);
			tmp->index = j++;
			add_token(&tok, tmp);
			i += ft_strlen(tmp->token);
		}
		else
			i++;
	}
	return (tok);
}
