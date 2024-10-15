/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:37:23 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:41 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *struct_env, char *dir)
{
	int		index;
	t_cmds	t_dir;
	int		i;

	i = 0;
	t_dir.cmd = malloc(sizeof(char *) * (2));
	t_dir.cmd[0] = "cd";
	t_dir.cmd[1] = dir;
	index = is_new_var_env(struct_env, &t_dir);
	while (struct_env->tab_env[index][i] != '=')
		i++;
	i++;
	free(t_dir.cmd);
	return (struct_env->tab_env[index] + i);
}

char	*display_dir(char *cmd, char *old_dir)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str;

	if (!old_dir)
		dir = opendir(".");
	else
		dir = opendir(old_dir);
	if (dir == NULL)
		return (NULL);
	if (dir == NULL)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(cmd, entry->d_name, 4) == 0)
		{
			str = ft_strdup(entry->d_name);
			closedir(dir);
			return (str);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}
