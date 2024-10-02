/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:37:52 by artberna          #+#    #+#             */
/*   Updated: 2024/10/02 14:12:25 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_env(char **env, char *s)
// {

// }

// static void	replace_dollar(char *s, char **env)
// {

// }

// static char	*copy_str(char *dest, char *src, int first, int second)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (src[i])
// 	{
// 		if (i == first || i == second)
// 			i++;
// 		else
// 			dest[j++] = src[i++];
// 	}
// 	dest[j] = '\0';
// 	return (dest);
// }

// static char	*remove_quote(char *s)
// {
// 	char	*tmp;
// 	int		i;
// 	int		start;

// 	i = 0;
// 	start = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 		{
// 			tmp = ft_calloc(ft_strlen(s) - 1, sizeof(char));
// 			if (!tmp)
// 				return (NULL);
// 			start = i;
// 			while (s[i] != s[start])
// 				i++;
// 			if (i > start && s[i] == s[start])
// 			{
// 				tmp = copy_str(tmp, s, start, i--);
// 				free(s);
// 				s = ft_strdup(tmp);
// 			}
// 			free(tmp);
// 		}
// 		i++;
// 	}
// 	return (s);
// }

static char	*remove_quote(char *s)
{
	int		s_quote;
	int		d_quote;
	int		i;
	int		j;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	d_quote = 0;
	s_quote = 0;
	i = 0;
	j = 0;
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
		else
			new_str[j++] = s[i++];
	}
	new_str[j] = '\0';
	free(s);
	return (new_str);
}

char	*get_clean_input(char *s, char **env, t_cmds *cmd)
{
	int	i;

	(void)env;
	(void)cmd;
	i = 0;
	if (s[0] == '\0' || !s)
		return (NULL);
	else
	{
		while (s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				s = remove_quote(s);
					return (s);
			}
			i++;
		}
	}
	return (s);
}
