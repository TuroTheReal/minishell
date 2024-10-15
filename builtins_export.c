/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsindres <dsindres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:45:47 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/08 14:14:21 by dsindres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_export(t_env *struct_env, t_cmds *t_cmds)
{
	int	i;

	i = is_new_var_env(struct_env, t_cmds);
	if (i != -1)
		my_export_replace(struct_env, t_cmds, i);
	else
		my_export_create(struct_env, t_cmds, struct_env->len);
}

int	is_new_var_env(t_env *struct_env, t_cmds *t_cmds)
{
	int		i;
	int		j;
	char	*new_path;

	i = 0;
	while (struct_env->tab_env[i])
	{
		j = 0;
		while (struct_env->tab_env[i][j] != '=')
			j++;
		new_path = ft_calloc(j + 1, sizeof(char));
		j = 0;
		while (struct_env->tab_env[i][j] != '=')
		{
			new_path[j] = struct_env->tab_env[i][j];
			j++;
		}
		if (ft_strncmp(new_path, t_cmds->cmd[1],
				(ft_strlen(new_path) + ft_strlen(t_cmds->cmd[1]))) == 0)
			return (free(new_path), i);
		free(new_path);
		i++;
	}
	return (-1);
}

void	my_export_create(t_env *struct_env, t_cmds *t_cmds, int len)
{
	int		i;
	int		j;
	char	**tab_var;

	i = 0;
	j = 0;
	tab_var = ft_calloc(len + 2, sizeof(char *));
	if (!tab_var)
		return ;
	while (struct_env->tab_env[i])
	{
		tab_var[i] = ft_strdup(struct_env->tab_env[i]);
		if (!tab_var[i])
		{
			free_double_tab(tab_var, i);
			return ;
		}
		i++;
	}
	my_export_create_2(struct_env, t_cmds, tab_var, i);
	return ;
}

void	my_export_create_2(t_env *struct_env, t_cmds *t_cmds,
		char **tab_var, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tab_var[index] = ft_calloc((ft_strlen(t_cmds->cmd[1])
				+ ft_strlen(t_cmds->cmd[2]) + 2), sizeof(char));
	while (t_cmds->cmd[1][i])
	{
		tab_var[index][i] = t_cmds->cmd[1][i];
		i++;
	}
	tab_var[index][i] = '=';
	i++;
	while (t_cmds->cmd[2][j])
	{
		tab_var[index][i] = t_cmds->cmd[2][j];
		i++;
		j++;
	}
	tab_var[index + 1] = NULL;
	free_double_tab(struct_env->tab_env, -1);
	struct_env->len++;
	struct_env->tab_env = tab_var;
	return ;
}

void	my_export_replace(t_env *struct_env, t_cmds *t_cmds, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free(struct_env->tab_env[index]);
	struct_env->tab_env[index] = NULL;
	struct_env->tab_env[index] = ft_calloc(ft_strlen(t_cmds->cmd[1])
			+ ft_strlen(t_cmds->cmd[2]) + 2, sizeof(char));
	while (t_cmds->cmd[1][i])
	{
		struct_env->tab_env[index][i] = t_cmds->cmd[1][i];
		i++;
	}
	struct_env->tab_env[index][i] = '=';
	i++;
	while (t_cmds->cmd[2][j])
	{
		struct_env->tab_env[index][i] = t_cmds->cmd[2][j];
		i++;
		j++;
	}
	struct_env->tab_env[index][i] = '\0';
	return ;
}
