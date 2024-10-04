/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:53:30 by artberna          #+#    #+#             */
/*   Updated: 2024/10/04 14:09:51 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_env(char *s, char **env)
// {
// 	int		i;
// 	char	*var;

// 	i = 0;
// 	if (!env || s[i] == '\0')
// 		return (NULL);
// 	while (env[i] && ft_strncmp(env[i], s, ft_strlen(s) + 1))
// 		i++;
// 	if (!env[i])
// 		return (NULL);
// 	var = ft_substr(env[i], ft_strlen(s) + 1, \
// 		ft_strlen(env[i]) - (ft_strlen(s) + 1));
// 	free(s);
// 	return (var);
// }

// static char	*make_dollar_var(char *s, char **env)
// {
// 	(void)env; // a remplacer par la struct
// 	char	*tmp;
// 	char	*to_ret;
// 	char	str[2];
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			// if i+j = ?, faire autre chose
// 			j = 1;
// 			while (s[i + j] && (s[i + j] != ' ' && s[i + j] != '$'))
// 				j++;
// 			tmp = ft_substr(s, i + 1, j - 1); // + 1, - 1 ?
// 			printf("TMP MAKE DOLLAR = %s~\n", tmp);
// 			if (!tmp)
// 				return (NULL);
// 			tmp = getenv(tmp);
// 			if (tmp)
// 			{
// 				if (!to_ret)
// 					to_ret = ft_strdup("");
// 				to_ret = ft_strjoin(to_ret, tmp);
// 			}
// 		i += j;
// 		}
// 		else
// 		{
// 			str[0] = s[i];
// 			str[1] = '\0';
// 			if (!to_ret)
// 					to_ret = ft_strdup("");
// 			to_ret = ft_strjoin(to_ret, str); // realloc ?
// 			i++;
// 		}
// 	}
// 	return (to_ret);
// }

// char	*replace_dollar(char *s, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*to_ret;

// 	i = 0;
// 	while (s[i])
// 	{
// 		j = 0;
// 		if (s[i] == '$')
// 		{
// 			to_ret = ft_substr(s, s[1], i); // + 1 ?
// 			if (!to_ret)
// 				exit_error("Substr failed");
// 			printf("TO_RET = %s~\n", to_ret);
// 			tmp = make_dollar_var(&s[i], env);
// 			to_ret = ft_strjoin(to_ret, tmp);
// 			return (free(s), to_ret);
// 		}
// 		i++;
// 	}
// 	return (s);
// }

// si il y a dollar, recuperer jusqua ' ' $ ou \0
// extraire la str en fonction des index au dessus
// chercher occurence de STR dans ENV avec STRRCHR
// si occurence, malloc NEW STR avec le variable dedans
// recuperer la STR avec variable pour join a STR du debut sans '$TERM'
