/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/18 15:08:04 by artberna         ###   ########.fr       */
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

static void	handle_sigint_child(int sig)
{
	static int	i;

	(void)sig;
	i = 0;
	signal(SIGINT, SIG_IGN);
	if (i >= 1)
		write(STDOUT_FILENO, "\n", 1);
	i++;
	sig_code = sig;
}

static void	init_child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handle_sigint_child);
}

static void	init_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	sig_code = sig;
}

void	init_signal(int option)
{
	if (option == 0)
	{
		printf("NORMAL MODE\n");
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 1)
	{
		printf("HDOC MODE\n");
		signal(SIGINT, init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 2)
	{
		printf("CHILD MODE\n");
		init_child_signal();
	}
}
