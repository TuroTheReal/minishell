/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/15 11:23:53 by artberna         ###   ########.fr       */
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

typedef struct s_std
{
	int		saved_stdout;
	int		saved_stdin;
}			t_std;

typedef struct s_env
{
	char	**tab_env;
	int		len;
}				t_env;

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
	t_env			*s_env;
}					t_gdata;

typedef struct s_cmds
{
	unsigned int	index;
	unsigned int	nb_redir;
	char			**cmd;
	int				flag_error;
	struct s_token	*redir;
	struct s_gdata	*g_data;
	struct s_std	*ptr_std;
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
t_cmds	*parser(t_token *tok, t_gdata *data);

// Parser Handler
void	parsenize(t_cmds *cmd, t_token *tok, t_gdata *data);

// Parser Utils
void	extend_cmd(t_cmds **cmd, t_gdata *data);
int		is_redir(t_token_type type);
int		is_cmd(t_token_type type);
void	free_cmd(t_cmds *cmd);
void	print_cmd(t_cmds *cmd); //debug

// Handle Dollar
void	handle_dollar(t_token *tok, t_env *s_env);

//Handle Redir
void	handle_redir(t_cmds *cmd, t_token **tok);

/******************************************************************************
#                                    DIEGO                                    *
#*****************************************************************************/

//Utils
void	putstr(char *str);
char	**copy_tab(char **env, int len);
void	free_double_tab(char **tab, int i);
int		init_struct_env(char **env, t_env *struct_env);
void	free_list(t_cmds *cmds);

//Builtins_cd_2
char	*display_dir(char *cmd, char *old_dir);
char	*ft_getenv(t_env *struct_env, char *dir);

//builtins_export
void	my_export(t_env *struct_env, t_cmds *t_cmds);
void	my_export_create(t_env *struct_env, t_cmds *t_cmds, int len);
void	my_export_create_2(t_env *struct_env, t_cmds *t_cmds,
			char **tab_var, int index);
void	my_export_replace(t_env *struct_env, t_cmds *t_cmds, int index);
int		is_new_var_env(t_env *struct_env, t_cmds *t_cmds);

#endif