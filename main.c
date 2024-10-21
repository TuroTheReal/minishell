/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/10/21 11:28:29 by artberna         ###   ########.fr       */
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

static void	minishell(t_gdata *data, t_token *tok, t_cmds *cmd)
{
	t_cmds	*test; // pour print sans bouger tete de liste
	while (1)
	{
		init_signal(0);
		data->input = readline("MINISHELL ~ ");
		if (!data->input)
			return ;
		add_history(data->input);
		tok = lexer(data);
		print_token(tok); // debug
		if (error_handler(&tok, data))
			continue ;
		cmd = parser(tok, data);
		if (!cmd || !cmd->cmd)
		{
			free_minishell(cmd, tok, data->input);
			continue ;
		}
		test = cmd; // debug
		print_cmd(test); // debug
		printf("NB COMMAND = %d\n", data->nb_command); // debug
		while (test) // debug
		{
			printf("STRUCT TOKEN CMD N%d\n", test->index);
			print_token(test->redir);
			test = test->next;
		}
		minishell_exec(cmd, &data->s_env);
		free_minishell(cmd, tok, data->input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_gdata	data;
	t_token	*tok;
	t_cmds	*cmd;

	(void)ac, (void)av;
	tok = NULL;
	cmd = NULL;
	if (init_struct_env(env, &data.s_env))
		return (EXIT_FAILURE);
	minishell(&data, tok, cmd);
	clear_history();
	free_double(data.s_env.tab_env);
	ft_putstr_fd("exit\n", 2);
	return (0);
}
