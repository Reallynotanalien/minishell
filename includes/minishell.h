#ifndef MINISHELL_H
# define MINISHELL_H

/*INCLUDES*/
# include <stdio.h>
# include "libft/libft.h"
# include "./readline/history.h"
# include "./readline/readline.h"
# include "exec.h"
# include "parsing.h"
# include "builtins.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

/*VARIABLES*/
# define ERROR 1
# define YES 1
# define NO 0
# define T_STR 1
# define T_SUBST 2
# define T_PIPE 3
# define T_HEREDOC 4
# define T_INFILE 5
# define T_OUTFILE 6
# define T_APPEND 7

/*ERROR MESSAGES*/
# define ARGC_ERROR "No argument should be sent appart from the program's name\n"
# define ENV_ERROR "The environment could not be copied\n"
# define ARGV_ERROR "There is no argv\n"
# define FIND_PATH_ERROR "Path was not found\n"

/*STRUCTS*/

typedef struct s_command
{
	int					infile;
	int					outfile;
	int					builtin_flag;
	char				*path;
	char				**cmd;
	struct s_command	*next;
}					t_command;

//This struct represents the tokens used for each readline return.
//They are seperated in different types defined in VARIABLES.
typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//This will be the main static struct, to be modified as we go!
typedef struct s_data
{
	struct s_token		*token;
	struct s_command	*cmd;
	int					error_flag;
	int					quote_flag;
	int					heredoc_flag;
	int					exstat;
	int					infile;
	int					outfile;
	int					fd[2];
	char				**new_env;
	char				*line;
	char				*line_cpy;
	struct termios		old_attributes;
	struct termios		new_attributes;
}				t_data;

//FUNCTIONS

//build_commands_utils.c
int			open_heredoc(t_token *tokens);
int			contains_whitespace(char *str);

//init.c
void		init_data(t_data *data);

//utils.c
t_data		*use_data(void);
void		view_list(void);

//linked_list.c
t_token		*add_token(char *token);
void		free_tokens_if_not_empty(void);
t_token		*lstget_prev(t_token *lst, t_token *reference);

//command_list.c
t_command	*create_command(void);
t_command	*add_command(char *command, int infile, int outfile);
void		free_commands_if_not_empty(void);
void		view_commands(void);

void		exec(t_command *cmd);

//path.c
char		*access_path(t_command *cmd, char **path_env);
char		*find_path(t_command **cmd, char **env);
t_command	*find_cmd(t_command **cmd);
void		get_path(t_command *cmd);

#endif