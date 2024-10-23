/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:39:46 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/23 17:11:49 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_fonctions(t_cmds *cmd, t_env *struct_env)
{
	if ((ft_strncmp(cmd->cmd[0], "env", 10) == 0) && cmd->cmd[1] == NULL)
		my_env(struct_env);
	else if ((ft_strncmp(cmd->cmd[0], "pwd", 10) == 0)
		&& cmd->cmd[1] == NULL)
		my_pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 10) == 0
		&& cmd->cmd[1] != NULL && cmd->cmd[2] != NULL)
		my_export(struct_env, cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 10) == 0
		&& cmd->cmd[1] != NULL)
		my_unset(struct_env, cmd);
	else if (ft_strncmp(cmd->cmd[0], "echo", 10) == 0)
		my_echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 10) == 0)
		my_cd(struct_env, cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", \
	ft_strlen(cmd->cmd[0])) == 0) // && cmd->cmd[1] != NULL)
		my_exit(struct_env, cmd);
	else
		return (ft_error("builtins fonctions", cmd), 1);
	return (0);
}

void	my_env(t_env *struct_env)
{
	int		i;

	i = 0;
	while (struct_env->tab_env[i])
	{
		putstr(struct_env->tab_env[i]);
		write(1, "\n", 1);
		i++;
	}
	return ;
}

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	putstr(pwd);
	write(1, "\n", 1);
	free (pwd);
	return ;
}

void	my_echo(char **cmd)
{
	int	i;

	if (cmd[1] == NULL)
		write(1, "\n", 1);
	else if (ft_strncmp(cmd[1], "-n", 4) == 0)
	{
		i = 2;
		while (cmd[i])
		{
			putstr(cmd[i]);
			i++;
		}
	}
	else if (ft_strncmp(cmd[1], "-n", 4) != 0)
	{
		i = 1;
		while (cmd[i])
		{
			putstr(cmd[i]);
			write(1, "\n", 1);
			i++;
		}
	}
}

void	print_var(char **tab_var)
{
	int	i;

	i = 0;
	while (tab_var[i])
	{
		putstr(tab_var[i]);
		write(1, "\n", 1);
		i++;
	}
}
