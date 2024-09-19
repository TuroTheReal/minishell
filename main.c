/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/09/19 17:06:57 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_gdata	*data;
	t_token	*tok;
	// t_cmds	*cmd;

	(void)ac;
	(void)av;
	(void)env;
	data = malloc(sizeof(t_gdata));
	ft_memset(data, 0, sizeof(t_gdata));
	while (1)
	{
		data->input = readline("minishell >");
		tok = lexer(data);
		if (input_error_handler(tok))
			continue; ;
		// cmd = parser(tok, env);
		// rl_on_new_line(); // a check
		print_token(tok);
		free_token(tok);
		free(data->input);
	}
	free(data);
	return (0);
}
