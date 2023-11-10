
#include "../../../includes/minishell.h"

/*The below function test the behavior of tokens surrounded by 
all symbols required to handle in the subject. 
Everything else is considered a string.
If an error should occur because of an invalid string, 
it will be handled by execve.
Only symbols right of the redirection is checked, as the error would 
have been caught earlier if a redirection symbol is present on left*/

int	next_isredirection(char *line, int index)
{
	if (ft_iswhitespace(line[index + 1]))
		index += 2;
	else
		index++;
	if ((!double_quoted(line, index) && !single_quoted(line, index))
		&& (line[index] == '<' || line[index] == '>' || line[index] == '|'))
		return (1);
	return (0);
}

//For '>>', index is the index of the first '>'.
int	parsing_redirection(char *line, int index)
{
	if (line[index + 1] && line[index] == line[index + 1] && line[index] != '|')
		index ++;
	if (!line[index + 1])
		return (parsing_error
			("syntax error near unexpected token 'newline'\n"));
	if (index == 0 && line[index] == '|')
		return (parsing_error
			("syntax error near unexpected token '|'\n"));
	if (next_isredirection(line, index))
	{
		if (ft_iswhitespace(line[index + 1]))
			index += 2;
		else
			index++;
		if (line[index + 1] && line[index] == line[index + 1])
			return (parsing_error(""),
				printf("syntax error near unexpected token '%c%c'\n",
					line[index], line[index]), ERROR);
		else
			return (parsing_error(""),
				printf("syntax error near unexpected token '%c'\n",
					line[index]), ERROR);
	}
	return (0);
}
