/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:14:10 by artberna          #+#    #+#             */
/*   Updated: 2024/10/02 14:31:36 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	remove_node(t_token *node, t_token **list)
// {
// 	if (node->prev == NULL)
// 	{
// 		*list = node->next;
// 		if (node->next)
// 			node->next->prev = NULL;
// 	}
// 	else
// 	{
// 		node->prev->next = node->next;
// 		if (node->next)
// 			node->next->prev = node->prev;
// 	}
// 	free(node->token);
// 	free(node);
// }

static char	**create_tab(char *str)
{
	char	**new_tab;

	new_tab = ft_calloc(sizeof(char *), 2);
	if (!new_tab)
		exit_error("Calloc failed");
	new_tab[0] = str;
	new_tab[1] = NULL;
	return (new_tab);
}

static void	add_to_tab(char *str, t_cmds *cmd)
{
	char	**tmp_tab;
	int		i;
	int		count;

	count = 0;
	if (cmd->cmd)
	{
		while (cmd->cmd[count])
			count++;
		tmp_tab = ft_calloc(sizeof(char *), count + 2);
		if (!tmp_tab)
			exit_error("Calloc failed");
		i = 0;
		while (i < count)
		{
			tmp_tab[i] = cmd->cmd[i];
			i++;
		}
		tmp_tab[i] = str;
		tmp_tab[i + 1] = NULL;
		free(cmd->cmd);
		cmd->cmd = tmp_tab;
	}
	else
		cmd->cmd = create_tab(str);
}

void	parsenize(t_cmds *cmd, t_token *tok, char **env, t_gdata *data)
{
	(void)env;
	while (tok)
	{
		if (tok->type == TOK_STR)
		{
			tok->token = get_clean_input(tok->token, env, cmd);
			// if (!tok->token)
			// 	continue ; // free tout ?
			// if (tok->token[0] == '\0')
			// 	remove_node(tok, &tok);
			add_to_tab(tok->token, cmd);
		}
		else if (tok->type == TOK_PIPE)
			extend_cmd(&cmd, data);
		// else if (is_redir(tok->type))
		// 	handle_redir(cmd, tok);
		tok = tok->next;
	}
}
