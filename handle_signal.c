/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/17 14:33:53 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_code = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig_code = sig;
}

static void	init_child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

static void	init_sigint_heredoc(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	sig_code = sig;
}

void	init_signal(int option)
{
	if (option == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 1)
	{
		signal(SIGINT, init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 2)
		init_child_signal();
}
