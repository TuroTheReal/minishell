/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/14 14:30:06 by artberna         ###   ########.fr       */
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
# define QUOTE_ERROR "minishell: syntax error near unexpected token 'quote'\n"

typedef enum e_token_type
{
	TOK_SPC,
	TOK_STR,
	TOK_S_Q,
	TOK_D_Q,
	TOK_IR,
	TOK_OR,
	TOK_APP,
	TOK_HDOC,
	TOK_PIPE,
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
	unsigned int	nb_command;
	char			*input;
	t_cmds			*s_cmds;
}					t_gdata;

typedef struct s_cmds
{
	unsigned int	index;
	unsigned int	nb_redir;
	char			**cmd;
	struct s_token	*redir;
	struct s_gdata	*g_data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

// Main
void	free_minishell(t_cmds *cmd, t_token *tok, char *input);

// Utils
void	exit_error(const char *s);
void	free_double(char **tab);

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
int		error_handler(t_token **tok, t_gdata *data);

// Parser
t_cmds	*parser(t_token *tok, t_gdata *data, char **env);

// Parser Handler
void	parsenize(t_cmds *cmd, t_token *tok, t_gdata *data);

// Parser Utils
void	extend_cmd(t_cmds **cmd, t_gdata *data);
int		is_redir(t_token_type type);
int		is_cmd(t_token_type type);
void	free_cmd(t_cmds *cmd);
void	print_cmd(t_cmds *cmd); //debug

// Handle Dollar
void	handle_dollar(t_token *tok, char **env);

//Handle Redir
void	handle_redir(t_cmds *cmd, t_token **tok);

/******************************************************************************
#                                    DIEGO                                    *
#*****************************************************************************/
#endif