#ifndef PARSING_H
# define PARSING_H

/*INCLUDES*/

/*ERROR MESSAGES*/
# define STRDUP_ERROR "Could not duplicate string.\n"
# define QUOTES_ERROR "found unclosed quotation marks\n"

/*STRUCTS*/

/*FUNCTIONS*/

//build_commands.c
void		build_commands(void);

//errors.c
int			parsing_error(char *error);
void		cleanup(void);
void		exit_program(void);
int			print_error(char *message);

//line_parsing.c
int			parse_quotes(char *str);
int			remove_spaces(char *str);
char		*ft_strtrim_whitespaces(char *str);

//parsing.c
int			main_parsing(int argc, char **argv, char **env);
void		parsing(void);
int			parsing_redirection(char *line, int index);
void		line_parsing(void);

//signals.c
void		signals(void);

//term_attributes.c
void		disable_ctrlc(void);
void		restore_attributes(void);

//token_parsing_utils.c
int			double_quoted(char *str, int index);
int			single_quoted(char *str, int index);

//token_split.c
int			split_tokens(void);
void		do_substitutions(char *line);
int			is_redirection(char c);
int			is_double_quote(char c);

#endif