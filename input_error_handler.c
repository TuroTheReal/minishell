/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:09:27 by artberna          #+#    #+#             */
/*   Updated: 2024/09/19 17:06:19 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_error_handler(t_token *tok)
{
	while (tok)
	{
		if (tok->token[0] == 'X')
		{
			free_token(tok);
			ft_printf("SYNTAX ERROR\n");
			rl_on_new_line();
			return (1);
		}
		if (tok->next)
			tok = tok->next;
		else
			return (0);
	}
	return (0);
}

