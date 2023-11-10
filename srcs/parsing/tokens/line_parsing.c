# include "../../../includes/minishell.h"

int	parse_quotes(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '\'' && !double_quoted(str, i))
			single_quotes++;
	double_quotes = 0;
	i = -1;
	while (str[++i] && !single_quoted(str, i))
		if (str[i] == '\"')
			double_quotes ++;
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (parsing_error(QUOTES_ERROR));
	return (0);
}

int	remove_spaces(char *str)
{
	char	*new_str;
	int		i;
	int		str_len;

	if (!str || !str[0])
		return (free (str), ERROR);
	i = -1;
	str_len = 0;
	while (str[++i])
		if (!ft_iswhitespace(str[i]) || double_quoted(str, i) 
			|| single_quoted(str, i)
			|| (i != 0 && !ft_iswhitespace(str[i - 1])))
			str_len++;
	new_str = ft_calloc(str_len + 1, sizeof(char));
	if (!new_str)
		return (free (str), ERROR);
	i = -1;
	str_len = 0;
	while (str[++i])
		if (!ft_iswhitespace(str[i]) || double_quoted(str, i) 
			|| single_quoted(str, i)
			|| (i != 0 && !ft_iswhitespace(str[i - 1])))
			new_str[str_len++] = str[i];
	use_data()->line_cpy = new_str;
	return (EXIT_SUCCESS);
}
