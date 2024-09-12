/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/09/12 14:23:00 by artberna         ###   ########.fr       */
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
	TOK_OPTION,
	TOK_OPERATOR,
	TOK_EOF,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*input;
}					t_token;

typedef enum e_type
{
	CMD,
	PIPE,
}	t_type;

typedef struct s_gdata
{
	unsigned int	nb_cmd;
	int				ifile;
	int				ofile;
	t_cmds			*s_cmds;
}					t_gdata;

typedef struct s_cmds
{
	t_type			type;
	unsigned int	nb_tok;
	char			*full_cmd;
	char			**cmd_tok_by_tok;
	struct s_gdata	*g_data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

/******************************************************************************
#                                    DIEGO                                    *
#*****************************************************************************/
#endif