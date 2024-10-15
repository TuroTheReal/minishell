/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:25:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/15 14:44:31 by artberna         ###   ########.fr       */
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
	// struct sigaction	signal;
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

// Utils Parsing
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

//Builtins_export
void	my_export(t_env *struct_env, t_cmds *t_cmds);
void	my_export_create(t_env *struct_env, t_cmds *t_cmds, int len);
void	my_export_create_2(t_env *struct_env, t_cmds *t_cmds,
			char **tab_var, int index);
void	my_export_replace(t_env *struct_env, t_cmds *t_cmds, int index);
int		is_new_var_env(t_env *struct_env, t_cmds *t_cmds);

//Minishell_exec
void	minishell_exec(t_cmds *cmds, t_env *struct_env);
void	multiple_commands(t_cmds *cmds, t_env *struct_env);
void	parent_process(int *fd, int *infile, pid_t pid);
void	child_process(t_cmds *temp, int infile, int *fd, t_env *struct_env);

//Minishell_exec_2
void	one_command(t_cmds *cmds, t_env *struct_env);
void	child_process_one_command(t_cmds *cmds, t_env *struct_env);
void	redirection(t_cmds *cmds, t_env *struct_env);
void	create_hdoc_file(t_cmds *cmds);
int		input_heredoc(t_token *temp_tok, char *line, int fd);

//Execution
void	execution(t_cmds *cmds, t_env *struct_env);
int		is_it_builtins(t_cmds *cmds);
void	exec_command(t_cmds *cmds, t_env *struct_env);
void	exec_command_2(t_cmds *cmds, t_env *struct_env);
char	*find_command(char *command, t_env *struct_env);

//Change_redirection
int		change_in_stdout(t_cmds *cmds);
int		saved_stdout(t_cmds *cmds, int file_fd);
int		change_out_stdout(t_cmds *cmds);
int		change_in_stdin(t_cmds *cmds);
int		change_out_stdin(t_cmds *cmds);

//Change_redirection_utils
t_token	*last_token_node(t_cmds *cmds, int flag);
int		create_file(t_cmds *cmds);
int		create_file_2(t_token *temp);
int		verif_file(t_cmds *cmds);
int		verif_file_2(char *file);

//Builtins_fonctions
int		builtins_fonctions(t_cmds *t_cmds, t_env *struct_env);
void	my_env(t_env *struct_env);
void	my_pwd(void);
void	my_echo(char **cmd);
void	print_var(char **tab_var);

//Builtins_export
void	my_export(t_env *struct_env, t_cmds *t_cmds);
void	my_export_create(t_env *struct_env, t_cmds *t_cmds, int len);
void	my_export_create_2(t_env *struct_env, t_cmds *t_cmds,
			char **tab_var, int index);
void	my_export_replace(t_env *struct_env, t_cmds *t_cmds, int index);
int		is_new_var_env(t_env *struct_env, t_cmds *t_cmds);

//Builtins_unset
void	my_unset(t_env *struct_env, t_cmds *t_cmds);
int		valide_value_env(char **env, char **cmd, int index);
void	my_unset_delete(t_env *struct_env, int index);

//Builtins_cd
void	my_cd(t_env *struct_env, t_cmds *t_cmds);
void	cd_dir_env(t_env *struct_env, char *dir);
void	cd_dir_move_up(t_env *struct_env, char *dir);
void	replace_dir(t_env *struct_env, char *old_dir,
			char *new_dir, char *new_old_dir);
void	cd_dir_path(t_env *struct_env, char *path);

//Builtins_cd_2
char	*display_dir(char *cmd, char *old_dir);
char	*ft_getenv(t_env *struct_env, char *dir);

//Utils
void	putstr(char *str);
char	**copy_tab(char **env, int len);
void	free_double_tab(char **tab, int i);
int		init_struct_env(char **env, t_env *struct_env);
void	free_list(t_cmds *cmds);

//Utils_exec_2
void	ft_error(char *str, t_cmds *cmds);
void	fork_error(t_cmds *temp, int *fd);
int		is_it_heredoc(t_cmds *cmds);
int		is_it_heredoc_2(t_cmds *cmds);
void	file_fd_value(t_token *in, int *file_fd);

#endif