/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:37:52 by artberna          #+#    #+#             */
/*   Updated: 2024/10/04 16:39:47 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*copy_str(char *new_str, char *s, int i, int j)
// {
// 	int		s_quote;
// 	int		d_quote;

// 	d_quote = 0;
// 	s_quote = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' && !d_quote)
// 		{
// 			s_quote = !s_quote;
// 			i++;
// 			continue ;
// 		}
// 		else if (s[i] == '\"' && !s_quote)
// 		{
// 			d_quote = !d_quote;
// 			i++;
// 			continue ;
// 		}
// 		new_str[j++] = s[i++];
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

// static int	get_len(char *s)
// {
// 	int		nb_quote;
// 	int		i;
// 	int		s_quote;
// 	int		d_quote;

// 	d_quote = 0;
// 	s_quote = 0;
// 	i = 0;
// 	nb_quote = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' && !d_quote)
// 		{
// 			s_quote = !s_quote;
// 			nb_quote++;
// 		}
// 		else if (s[i] == '\"' && !s_quote)
// 		{
// 			d_quote = !d_quote;
// 			nb_quote++;
// 		}
// 		i++;
// 	}
// 	return (i - nb_quote);
// }

// static char	*remove_quote(char *s)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	int		len;

// 	len = get_len(s);
// 	i = 0;
// 	j = 0;
// 	new_str = ft_calloc(len + 1, sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	new_str = copy_str(new_str, s, i, j);
// 	free(s);
// 	return (new_str);
// }

// char	*get_clean_input(char *s, char **env)
// {
// 	int	i;

// 	i = 0;
// 	if (s[0] == '\0' || !s)
// 		return (NULL);
// 	else
// 	{
// 		while (s[i])
// 		{
// 			if (s[i] == '\'')
// 				return (remove_quote(s));
// 			else if (s[i] == '\"')
// 			{
// 				s = remove_quote(s);
// 				return (replace_dollar(s, env));
// 			}
// 			else if (s[i] == '$')
// 				return (replace_dollar(s, env));
// 			i++;
// 		}
// 	}
// 	return (s);
// }

static char	*copy_str(char *dest, char *src, int limit)
{
	char	*to_join;
	char	*to_return;

	to_join = ft_substr(src, 0, limit);
	if (!to_join)
		exit_error("substr failed");
	to_return = ft_strjoin(dest, to_join);
	if (!to_return)
		exit_error("strjoin failed");
	free(dest);
	free(to_join);
	return (to_return);
}

static int	remove_quote(char **dest, char *src)
{
	int	i;

	i = 0;
	if (src[i] == '\'')
	{
		i++;
		while (src[i] != '\'')
			i++;
		*dest = copy_str(*dest, src + 1, i - 1);
		return (i + 1);
	}
	else if (src[i] == '\"')
	{
		i++;
		while (src[i] != '\"')
			i++;
		*dest = copy_str(*dest, src + 1, i - 1);
		// replace_dollar(dest, src, i);
		return (i + 1);
	}
	return (0);
}

static char	*ft_realloc(void *s, int old_size, int new_size)
{
	char	*ret;

	if (!new_size || new_size <= 0)
		return (free(s), NULL);
	ret = malloc(new_size);
	if (!ret)
		return (free(s), NULL);
	if (s)
	{
		ft_memcpy(ret, s, old_size);
		free(s);
	}
	return (ret);
}

static char	*quote_n_dollar(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			i += remove_quote(&dest, &src[i]);
		// else if (src[i] == '$')
		// 	i += replace_dollar(&dest, &src[i]);
		else
		{
			j = ft_strlen(dest);
			dest = ft_realloc(dest, j, j + 2);
			dest[j] = src[i];
			dest[j + 1] = '\0';
			i++;
		}
	}
	return (dest);
}

char	*get_clean_input(char *s, char **env)
{
	char	*new_str;

	(void)env;
	new_str = ft_strdup("");
	if (!new_str)
		exit_error("strdup failed");
	if (s[0] == '\0' || !s)
		return (NULL);
	new_str = quote_n_dollar(new_str, s);
	free(s);
	return (new_str);
}
