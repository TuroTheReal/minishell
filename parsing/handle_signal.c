/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/22 14:54:08 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_code = sig;
	printf ("SIGCODE = %d \n", g_sig_code);
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
	g_sig_code = sig;
	printf ("CHILD SIGCODE = %d \n", g_sig_code);
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
	g_sig_code = sig;
	printf ("HDOD SIGCODE = %d \n", g_sig_code);
}

void	init_signal(int option)
{
	if (option == 0)
	{
		// printf("NORMAL MODE\n"); //debug
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 1)
	{
		printf("HDOC MODE\n"); //debug
		signal(SIGINT, init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 2)
	{
		printf("CHILD MODE\n"); //debug
		init_child_signal();
	}
}
