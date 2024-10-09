/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:06:58 by artberna          #+#    #+#             */
/*   Updated: 2024/10/09 16:37:49 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	adjust_len(char *s)
{
	int	i;

	i = 1;
	printf("ADJUST LEN STR = %s\n", s);
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			break ;
		i++;
	}
	printf("ADJUST LEN %d\n", i);
	return (i);
}

static char	*copy_str(char *str, char c)
{
	int		len;
	char	*new_str;

	if (!str)
		str = ft_strdup("");
	len = ft_strlen(str);
	new_str = ft_realloc(str, len, len + 2);
	if (!new_str)
		return (free(str), NULL);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

static char	*extract_dollar_n_replace(char *s, char **env, int index)
{
	int		start;
	char	*to_ret;
	char	*to_find;
	char	*var;

	(void)env;
	to_ret = NULL;
	start = index;
	while (s[index] && (ft_isalnum(s[index]) || s[index] == '_'))
		index++;
	to_find = ft_substr(s, start + 1, index - start - 1);
	if (!to_find)
		return (NULL);
	printf("TOFIND = %s\n", to_find);
	var = getenv(to_find);
	printf("VAR = %s\n", var);
	free(to_find);
	if (var)
		to_ret = ft_strdup(var);
	else
		to_ret = ft_strdup("");
	return (to_ret);
}

static char	*replace_dollar(char *s, char **env)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			tmp = extract_dollar_n_replace(s, env, i);
			result = ft_realloc(result, ft_strlen(result), \
			ft_strlen(result) + ft_strlen(tmp) + 1);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i += adjust_len(s);
		}
		else
			result = copy_str(result, s[i++]);
	}
	return (result);
}

void	handle_dollar(t_token *tok, char **env)
{
	char	*new_token;

	while (tok)
	{
		if (tok->type == TOK_STR || tok->type == TOK_D_Q)
		{
			new_token = replace_dollar(tok->token, env);
			if (new_token)
			{
				free(tok->token);
				tok->token = new_token;
			}
		}
		tok = tok->next;
	}
}
