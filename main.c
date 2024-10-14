/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/10/14 14:32:48 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_cmds *cmd, t_token *tok, char *input)
{
	if (cmd)
		free_cmd(cmd);
	if (tok)
		free_token(tok);
	if (input)
		free(input);
	rl_on_new_line();
}

static void	minishell(t_gdata *data, t_token *tok, t_cmds *cmd, char **env)
{
	(void)env;
	while (1)
	{
		data->input = readline("minishell > ");
		if (!data->input)
			return ;
		add_history(data->input);
		tok = lexer(data);
		print_token(tok); // debug
		if (error_handler(&tok, data))
			continue ;
		cmd = parser(tok, data, env);
		if (!cmd)
		{
			free_minishell(NULL, tok, data->input);
			continue ;
		}
		// print_cmd(cmd); // debug
		printf("NB COMMAND = %d\n", data->nb_command); // debug
		while (cmd) // debug, free manquant si actif
		{
			printf("STRUCT TOKEN CMD N%d\n", cmd->index);
			print_token(cmd->redir);
			cmd = cmd->next;
		}
		//if (exec(cmd, data, env) == pas bon)
			// continue ;
		free_minishell(cmd, tok, data->input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_gdata	*data;
	t_token	*tok;
	t_cmds	*cmd;

	(void)ac;
	(void)av;
	tok = NULL;
	cmd = NULL;
	data = malloc(sizeof(t_gdata));
	ft_memset(data, 0, sizeof(t_gdata));
	minishell(data, tok, cmd, env);
	clear_history();
	free(data);
	return (0);
}
