/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:37:52 by artberna          #+#    #+#             */
/*   Updated: 2024/10/03 17:06:16 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_str(char *new_str, char *s, int i, int j)
{
	int		s_quote;
	int		d_quote;

	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d_quote)
		{
			s_quote = !s_quote;
			i++;
			continue ;
		}
		else if (s[i] == '\"' && !s_quote)
		{
			d_quote = !d_quote;
			i++;
			continue ;
		}
		new_str[j++] = s[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

static int	get_len(char *s)
{
	int		nb_quote;
	int		i;
	int		s_quote;
	int		d_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	nb_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d_quote)
		{
			s_quote = !s_quote;
			nb_quote++;
		}
		else if (s[i] == '\"' && !s_quote)
		{
			d_quote = !d_quote;
			nb_quote++;
		}
		i++;
	}
	return (i - nb_quote);
}

static char	*remove_quote(char *s)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = get_len(s);
	i = 0;
	j = 0;
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = copy_str(new_str, s, i, j);
	free(s);
	return (new_str);
}

char	*get_clean_input(char *s, char **env)
{
	int	i;

	i = 0;
	if (s[0] == '\0' || !s)
		return (NULL);
	else
	{
		while (s[i])
		{
			if (s[i] == '\'')
				return (remove_quote(s));
			else if (s[i] == '\"')
			{
				s = remove_quote(s);
				return (replace_dollar(s, env));
			}
			else if (s[i] == '$')
				return (replace_dollar(s, env));
			i++;
		}
	}
	return (s);
}
