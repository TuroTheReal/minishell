/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/10/03 11:57:10 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_minishell(t_cmds *cmd, t_token *tok, char *input)
{
	free_cmd(cmd);
	free_token(tok);
	free(input);
	rl_on_new_line();
}

static void	minishell(t_gdata *data, t_token *tok, t_cmds *cmd, char **env)
{
	while (1)
	{
		data->input = readline("minishell > ");
		if (!data->input)
			return ;
		add_history(data->input);
		tok = lexer(data);
		if (input_error_handler(&tok, data))
			continue ;
		print_token(tok); // debug
		cmd = parser(tok, data, env);
		if (!cmd)
		{
			free_minishell(NULL, tok, data->input);
			continue ;
		}
		print_cmd(cmd); // debug
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
