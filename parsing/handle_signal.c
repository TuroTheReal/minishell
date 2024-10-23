/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/23 09:58:10 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal = {0,0};

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal.sig_code = sig + SIGOFFSET;
	printf ("SIGCODE = %d \n", g_signal.sig_code);
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
	g_signal.sig_code = sig + SIGOFFSET;
	printf ("CHILD SIGCODE = %d \n", g_signal.sig_code);
}

static void	init_child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, handle_sigint_child);
}

static void	init_sigint_heredoc(int sig)
{
	(void)sig;
	if (g_signal.heredoc != 1)
	{
		g_signal.heredoc = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal.sig_code = sig + SIGOFFSET;
		printf ("HDOC SIGCODE = %d \n", g_signal.sig_code);
		exit(EXIT_FAILURE);
	}
}

void	init_signal(int option)
{
	if (option == 0)
	{
		printf("NORMAL MODE\n"); //debug
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 1)
	{
		printf("HDOC MODE\n"); //debug
		g_signal.heredoc = 0;
		signal(SIGINT, init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 2)
	{
		printf("CHILD MODE\n"); //debug
		init_child_signal();
	}
}
