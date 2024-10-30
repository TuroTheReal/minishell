/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:24:45 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/30 14:52:50 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_cmds *cmds, t_env *struct_env)
{
	if (is_it_builtins(cmds) == 0)
	{
		if (builtins_fonctions(cmds, struct_env) == 1)
			return ;
	}
	else if (is_it_builtins(cmds) == 2)
		return ;
	else
		exec_command(cmds, struct_env);
}

int	is_it_builtins(t_cmds *cmds)
{
	if (cmds == NULL || cmds->cmd == NULL || cmds->cmd[0] == NULL)
		return (2);
	if (ft_strncmp(cmds->cmd[0], "env", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "pwd", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "cd", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "export", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "unset", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "echo", 10) == 0
		|| ft_strncmp(cmds->cmd[0], "exit", 10) == 0)
		return (0);
	return (1);
}

void	exec_command(t_cmds *cmds, t_env *struct_env)
{
	if (access(cmds->cmd[0], F_OK) == 0)
	{
		printf("la\n\n");
		if (access(cmds->cmd[0], X_OK) == -1)
		{
			perror(cmds->cmd[0]);
			exit(126);
		}
		if (execve(cmds->cmd[0], cmds->cmd, struct_env->tab_env) == -1)
		{
			perror("Execve 1 ");
			exit(126);
		}
	}
	else
	{
		if (ft_getenv(struct_env, "PATH", cmds->g_data))
			exec_command_2(cmds, struct_env);
		else
		{
			my_error(cmds->cmd[0] \
			, ": No such file or directory\n", cmds);
			exit(127);
		}
	}
}

void	exec_command_2(t_cmds *cmds, t_env *struct_env)
{
	char	*path;

	path = find_command(cmds->cmd[0], struct_env);
	if (!path)
	{
		if (ft_strstr(cmds->cmd[0], "/"))
			my_error(cmds->cmd[0], ": No such file or directory\n", cmds);
		else
			my_error(cmds->cmd[0], ": command not found\n", cmds);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		free(path);
		perror(path);
		exit(126);
	}
	if (execve(path, cmds->cmd, struct_env->tab_env) == -1)
	{
		free(path);
		ft_error("Execve 1", cmds, 1);
	}
}

char	*find_command(char *command, t_env *struct_env)
{
	int		i;
	char	**long_path_split;
	char	*path_split;
	char	*final_path;

	i = 0;
	while (struct_env->tab_env[i]
		&& ft_strnstr(struct_env->tab_env[i], "PATH", 4) == NULL)
		i++;
	long_path_split = ft_split(struct_env->tab_env[i] + 5, ':');
	i = 0;
	while (long_path_split[i])
	{
		path_split = ft_strjoin_no_free(long_path_split[i], "/");
		final_path = ft_strjoin_no_free(path_split, command);
		free(path_split);
		if (access(final_path, F_OK) == 0)
		{
			free_double_tab(long_path_split, -1);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	return (free_double_tab(long_path_split, -1), NULL);
}
