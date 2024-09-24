/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/09/24 10:47:59 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "my_library/my_library.h"

/******************************************************************************
#                                    ARTHUR                                   *
#*****************************************************************************/

typedef struct s_cmds	t_cmds;

# define IS_TOKEN "<>|\'\""
# define PIPE_ERROR "minishell: syntax error near unexpected token \'|\'\n"
# define NL_ERROR "minishell: syntax error near unexpected token 'new_line'\n"
# define IR_ERROR "minishell: syntax error near unexpected token '>'\n"
# define OR_ERROR "minishell: syntax error near unexpected token '<'\n"
# define APP_ERROR "minishell: syntax error near unexpected token '>>'\n"
# define HDOC_ERROR "minishell: syntax error near unexpected token '<<'\n"

typedef enum e_token_type
{
	TOK_STR,
	TOK_IR,
	TOK_OR,
	TOK_APP,
	TOK_HDOC,
	TOK_PIPE,
	TOK_COMMAND,
	TOK_ARG,
	TOK_FILE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				index;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_gdata
{
	unsigned int	nb_cmd;
	char			*input;
	t_cmds			*s_cmds;
}					t_gdata;

typedef enum e_cmd_type
{
	CMD,
	PIPE,
	BUILTIN,
	HEREDOC,
}	t_cmd_type;

typedef struct s_cmds
{
	unsigned int	index;
	t_cmd_type		type_redir;
	char			**cmd;
	int				ifile;
	int				ofile;
	struct s_gdata	*g_data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

// Utils
void	exit_error(const char *s);

// Lexer
t_token	*lexer(t_gdata *data);

// Lexer Handler
t_token	*tokenize(char *s);

// Lexer Utils
t_token	*create_token(const char *s, int len, t_token_type type);
void	add_token(t_token **tok, t_token *new_node);
void	free_token(t_token *tok);
void	print_token(t_token *tok); //debug

// Error Input Handler
int		input_error_handler(t_token **tok, t_gdata *data);

// Parser
t_cmds	*parser(t_token *tok, char **env);

// Parser Handler


// Parser Utils
/******************************************************************************
#                                    DIEGO                                    *
#*****************************************************************************/
#endif