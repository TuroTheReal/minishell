/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:06:58 by artberna          #+#    #+#             */
/*   Updated: 2024/10/08 14:44:11 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_dollar(char *s, char **env)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*debut;
	int		start;

	(void)env;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = i;
			debut = ft_substr(s, start, i);
			while (ft_isalnum(s[i]) && s[i] == '_')
				i++;
			tmp = ft_substr(s, start + 1, i);
			var = getenv(tmp);
			free(tmp);
			debut = ft_strjoin(debut, var);
			free(var);
		}
		i++;
	}
	return (debut);
}

void	handle_dollar(t_token *tok, char **env)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (tok->type == TOK_D_Q || tok->type == TOK_STR)
			tok->token = replace_dollar(tok->token, env);
		tok = tok->next;
	}
}
