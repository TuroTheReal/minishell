/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/09/26 13:30:11 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_gdata *data, t_token *tok, t_cmds *cmd, char **env)
{
	(void)env;
	(void)cmd;
	while (1)
	{
		data->input = readline("minishell > ");
		if (!data->input)
			return ;
		add_history(data->input);
		tok = lexer(data);
		if (input_error_handler(&tok, data))
			continue ;
		// cmd = parser(tok, env, data);
		// if (!cmd)
		// 	return (free(data->input), free_token(tok)); // continue ? // rl_on_new_line(); ?
		print_token(tok);
		//if (exec(cmd, data, env) == pas bon)
			// continue;
		free_token(tok);
		free(data->input);
		rl_on_new_line();
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
