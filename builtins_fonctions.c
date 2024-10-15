/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsindres <dsindres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:39:46 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/08 14:11:17 by dsindres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_fonctions(t_cmds *t_cmds, t_env *struct_env)
{
	if ((ft_strncmp(t_cmds->cmd[0], "env", 10) == 0) && t_cmds->cmd[1] == NULL)
		my_env(struct_env);
	else if ((ft_strncmp(t_cmds->cmd[0], "pwd", 10) == 0)
		&& t_cmds->cmd[1] == NULL)
		my_pwd();
	else if (ft_strncmp(t_cmds->cmd[0], "export", 10) == 0
		&& t_cmds->cmd[1] != NULL && t_cmds->cmd[2] != NULL)
		my_export(struct_env, t_cmds);
	else if (ft_strncmp(t_cmds->cmd[0], "unset", 10) == 0
		&& t_cmds->cmd[1] != NULL)
		my_unset(struct_env, t_cmds);
	else if (ft_strncmp(t_cmds->cmd[0], "echo", 10) == 0)
		my_echo(t_cmds->cmd);
	else if (ft_strncmp(t_cmds->cmd[0], "cd", 10) == 0)
		my_cd(struct_env, t_cmds);
	//else if (ft_strncmp(t_cmds->cmd[0], "exit", 10) == 0
	//	&& t_cmds->cmd[1] != NULL)
	//	my_exit(struct_env, t_cmds);
	else
	{
		ft_error("builtins fonctions ", t_cmds);
		return (1);
	}
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

	if (ft_strncmp(cmd[1], "-n", 4) == 0)
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
