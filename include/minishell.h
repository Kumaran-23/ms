#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

// Token types
// builtin : builtin cmd: e.g. echo, cd
// cmd: any type of other command
// arg : any type of argument
// input : '<' 
// heredoc : '<<'
// trunc : '>'
// append : '>>'
// pipe : '|'

# define BUILTIN 1
# define CMD 2
# define ARG 3
# define INPUT 4
# define HEREDOC 5
# define TRUNC 6
# define APPEND 7
# define PIPE 8

// str - token string
// type - token type
// prev and next - linked list pointers to previous and next token

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	t_token		*tokens;
	int			cmd;
	int			pipe_read;
	int			pipe_write;
	int			input;
	int			output;
	int			stdin;
	int			stdout;
	int			execute_code;
}	t_mini;

//init signals, pipes etc
typedef struct s_global
{
	int		sigint;
	t_mini	*mini;
	int		pipe;
}	t_global;

extern t_global g_global;

//parser
int		ft_strcmp(char *s1, char *s2);
void	print_tokens(t_token *tokens);
int		builtin_cmd(char *token);
int		delim_token(char *token);
int		token_type(t_mini *mini, char *token);
t_token	*new_token(t_mini *mini, char *data);
void	token_addend(char *data, t_mini *mini);
int		create_pipe(t_mini *mini);
int		redirect_output(t_mini *ms, t_token *token, int type);
int		redirect_input(t_mini *ms, t_token *token);
void	parse(t_mini *mini, char *buff);

//execute
int		count_argc(char **args);
void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok);
char	**convert_argv(t_token	*tokens);
int		call_builtin(char **argv, char *command, t_mini *ms);
int		execute_builtin(char **argv, char *command, t_mini *ms);
int		execute(t_mini *mini);

//builtin_commands
int		echo(int argc, char **argv);
int		pwd(void);
int		mini_exit(t_mini *ms, char **agrv);

//free
void	token_free(t_token *tok);
void	agrv_free(char **argv);

#endif