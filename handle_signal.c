/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/23 17:30:45 by artberna         ###   ########.fr       */
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
	g_sig_code = sig + SIGOFFSET;
	printf ("SIGCODE = %d \n", g_sig_code);
}

static void	handle_sigint_child(int sig)
{
	static int	i;

	i = 0;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, SIG_IGN);
	if (i >= 1)
		write(STDOUT_FILENO, "\n", 1);
	i++;
	g_sig_code = sig + SIGOFFSET;
	printf ("CHILD SIGCODE = %d \n", g_sig_code);
}

static void	handle_sigquit_child(int sig)
{
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	g_sig_code = sig + SIGOFFSET;
	printf ("CHILD SIGCODE = %d \n", g_sig_code);
}

static void	init_child_signal(void)
{
	printf("CHILD MODE\n"); //debug
	signal(SIGQUIT, handle_sigquit_child);
	signal(SIGINT, handle_sigint_child);
}

static void	init_sigint_heredoc(int sig, int *heredoc)
{
	(void)sig;
	if (*heredoc != 1)
	{
		*heredoc = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig_code = sig + SIGOFFSET;
		printf ("HDOC SIGCODE = %d \n", g_sig_code);
		exit(EXIT_SUCCESS);
	}
}

void	init_signal(int option, int *heredoc)
{
	(void)heredoc;
	if (option == 0)
	{
		printf("NORMAL MODE\n"); //debug
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (option == 1)
	{
		printf("HDOC MODE\n"); //debug
		signal(SIGINT, (void (*)(int))init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (option == 2)
		init_child_signal();
}
