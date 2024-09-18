/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:46:15 by artberna          #+#    #+#             */
/*   Updated: 2024/09/18 17:12:05 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(t_gdata *data)
{
	int		i;
	int		j;
	t_token	*tok;
	t_token	*tmp;

	tok = NULL;
	i = 0;
	j = 0;
	while (data->input[i])
	{
		if (data->input[i] != ' ' && data->input[i] != '\t')
		{
			tmp = tokenize(&data->input[i]);
			if (!tmp)
				return (free_token(tok), NULL);
			tmp->index = j++;
			add_token(&tok, tmp);
			i += ft_strlen(tmp->token);
		}
		else
			i++;
	}
	print_token(tok);
	free_token(tok);
	return (tok);
}
