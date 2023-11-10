# include "../../includes/minishell.h"

/*Checks if the minishell args are valid and makes a copy
of the env variable to be used later.*/
int	main_parsing(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (print_error(ARGC_ERROR));
	use_data()->new_env = env;
	if (!use_data()->new_env)
		return (print_error(ENV_ERROR));
	if (!argv)
		return (print_error(ARGV_ERROR));
	return (0);
}

/*First checks if all the quotes are closed, if not, returns ERROR
and sets the error flag to ERROR.
Then, removes all of the superfluous spaces in between words (except
for what's in between quotes), returns ERROR if something goes wrong
and sets the error flag to ERROR.
Then substitutes all of the environment variables it finds in the 
command line and stores it in a copy of the original line.
After all of that is done, splits the line into tokens. If something
goes wrong, the tokens are freed as well as the copy of the line.
Those tokens are then used to create a command list, in which each 
command will be associated with the right input and output file for
easy execution.*/
void	line_parsing(void)
{
	if (parse_quotes(use_data()->line) == ERROR)
		return ;
	if (remove_spaces(use_data()->line) == ERROR)
		return (free(use_data()->line_cpy));
	do_substitutions(use_data()->line_cpy);
	if (split_tokens() == ERROR)
		return (free_tokens_if_not_empty(), free(use_data()->line_cpy));
	// view_list();
	//check whitespaces function because now the éèà characters won't print 
	//if they are at the beginning of a sentence
	build_commands();
	// view_commands();
	free_tokens_if_not_empty();
}
