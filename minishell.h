/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/09/12 16:29:28 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "my_library/my_library.h"

/******************************************************************************
#                                    ARTHUR                                   *
#*****************************************************************************/

typedef struct s_cmds	t_cmds;

typedef enum e_token_type
{
	TOK_CMD,
	TOK_ARG,
	TOK_PIPE,
	TOK_I_REDIR,
	TOK_O_REDIR,
	TOK_PIPE,
	TOK_EOF,
	TOK_S_QUOTE,
	TOK_D_QUOTE,
	TOK_OTHERS,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*input;
}					t_token;

typedef struct s_gdata
{
	unsigned int	nb_cmd;
	int				ifile;
	int				ofile;
	t_cmds			*s_cmds;
}					t_gdata;

typedef enum e_cmd_type
{
	CMD,
	PIPE,
	HEREDOC,
	I_FILE,
	O_FILE,
}	t_cmd_type;

typedef struct s_cmds
{
	unsigned int	index;
	t_cmd_type		type;
	unsigned int	nb_tok;
	char			**cmd;
	struct s_gdata	*g_data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

/******************************************************************************
#                                    DIEGO                                    *
#*****************************************************************************/
#endif