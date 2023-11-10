# include "../../../includes/minishell.h"

// char	*join_and_free(char *command, const char *token)
// {
// 	char			*temp;
// 	unsigned int	len1;
// 	unsigned int	len2;

// 	len1 = find_len_until(command, '\0');
// 	len2 = find_len_until(token, '\0');
// 	if (!null_calloc(&temp, sizeof (char), (len1 + len2 + 1)))
// 	{
// 		free_if_not_empty(&command);
// 		return (NULL);
// 	}
// 	copy_from_src(temp, command, len1);
// 	copy_from_src(temp + len1, token, len2);
// 	free_if_not_empty(&command);
// 	return (temp);
// }

t_token	*command_loop(t_token *tokens, char **command)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			break ;
		else if (tokens->type == T_HEREDOC)
			use_data()->infile = open_heredoc(tokens);
		else if (tokens->type == T_INFILE)
			printf("infile = open_infile();\n");
		else if (tokens->type == T_OUTFILE || tokens->type == T_APPEND)
			printf("outfile = open_outfile();\n");
		else if (tokens->type == T_STR)
		{
			*command = join_free(*command, " ");
			*command = join_free(*command, tokens->token);
		}
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
	return (tokens);
}

// void	open_pipe(void)
// {
// 	if (pipe(use_data()->fd) < 0)
// 		printf("PIPE ERROR\n");
// 	use_data()->outfile = use_data()->fd[1];
// }

void	build_commands(void)
{
	t_token	*tokens;
	char	*command;
	int		i;

	i = 1;
	tokens = use_data()->token;
	while (tokens)
	{
		command = NULL;
		if (tokens->prev && tokens->prev->type == T_PIPE)
			use_data()->infile = use_data()->fd[0];
		else
			use_data()->infile = STDIN_FILENO;
		use_data()->outfile = STDOUT_FILENO;
		tokens = command_loop(tokens, &command);
		if (tokens->type == T_PIPE)
			printf("open pipe\n");
		add_command(command, use_data()->infile, use_data()->outfile);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
}
