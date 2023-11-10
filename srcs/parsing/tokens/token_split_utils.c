# include "../../../includes/minishell.h"

/*Returns yes if the character is a redirection character
(|, < or >).*/
int	is_redirection(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	return (NO);
}

/*Returns yes if the character is a double quote.*/
int	is_double_quote(char c)
{
	if (c == '"')
		return (YES);
	return (NO);
}
