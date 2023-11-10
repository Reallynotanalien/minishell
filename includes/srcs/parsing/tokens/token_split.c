# include "../../../includes/minishell.h"

/*Iterates until it finds another double quote character.*/
int	iterate_until_quotes_are_closed(char *line, int end)
{
	while (line[end + 1] && !is_double_quote(line[end + 1]))
		end++;
	if (!ft_iswhitespace(line[end + 1]))
		return (end);
	return (end + 1);
}

/*Iterates until a redirection character is found. If it finds a double
quote, iterates until it finds the closing quote so that we do not
include any redirection character that is contained between those quotes
into our count, since those will be part of the string.*/
int	iterate_until_redir(char *line, int end, int start)
{
	if (start == 0 && is_double_quote(use_data()->line_cpy[start]))
	{
		end = iterate_until_quotes_are_closed(use_data()->line_cpy, end + 1);
		end++;
	}
	while (line[end] && line[end + 1]
		&& !is_redirection(line[end + 1]))
	{
		if (line[end + 1] == '"')
			end = iterate_until_quotes_are_closed(line, end + 1);
		end++;
	}
	return (end);
}

int	iterate_until_space(char *line, int end)
{
	while (line[end] && line[end + 1]
		&& !ft_iswhitespace(line[end + 1]))
	{
		if (line[end + 1] == '"')
			end = iterate_until_quotes_are_closed(line, end + 1);
		end++;
	}
	return (end);
}

/*Copies the part of the command line that we want as a token and
deletes all of the superfluous whitespaces that would be before or
after the string. 
Then the token gets created and the string is freed.*/
void	new_token(int start, int end)
{
	char	*token;

	token = ft_substr(use_data()->line_cpy, start, (end - start + 1));
	token = ft_strtrim_whitespaces(token);
	add_token(token);
	free(token);
}

/*Iterates through the line and splits it into a linked list of tokens.
Everytime there is a redirection, it gets splitted into it's own token
with all of the words that follows it, until the next redirection. 
If a redirection is found in between double quotes, it gets treated as part
of the string and not as a redirection.
Everytime there is a pipe, the pipe gets put into a token all alone.
All of the superfluous whitespaces that would be in between tokens are also
deleted.
This function works wether the strings and the redirections are separated by
a space or not. (Ex: cat | cat OR cat|cat both work.).*/
int	split_tokens(void)
{
	size_t	start;
	int		end;

	start = 0;
	while (use_data()->line_cpy[start]
		&& start <= ft_strlen(use_data()->line_cpy))
	{
		end = start;
		if (!is_redirection(use_data()->line_cpy[start]))
			end = iterate_until_redir(use_data()->line_cpy, end, start);
		else
		{
			if (parsing_redirection(use_data()->line_cpy, start) == ERROR)
				return (ERROR);
			end++;
			if (use_data()->line_cpy[start] == '<'
				|| use_data()->line_cpy[start] == '>')
				end = iterate_until_space(use_data()->line_cpy, end);
		}
		new_token(start, end);
		start = end + 1;
	}
	return (0);
}
