# include "../../../includes/minishell.h"

/*Opens a temporary file called .here_doc and uses get_next_line to take input
from the terminal and put it in that file. It is then closed, then reopened
in RD_ONLY mode to use as input for the program. The output file is opened
with O_APPEND to deal with << >>.*/
int	open_heredoc(t_token *tokens)
{
	char	*str;
	char	*token;
	int		temp_file;
	int		here_doc;

	temp_file = open(".here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	token = ft_strtrim_whitespaces(ft_substr(tokens->token, 2, ft_strlen(tokens->token) - 2));
	if (tokens->next && tokens->next->type == T_STR)
		printf("Heredoc should not work here because there is something else than a redirection after the EOF\n");
	while (get_next_line(0, &str))
	{
		if ((ft_strlen(str) == ft_strlen(token) + 1)
			&& (ft_strncmp(str, token, ft_strlen(token)) == 0))
		{
			free(str);
			break ;
		}
		else
			write(temp_file, str, ft_strlen(str));
		free(str);
	}
	close(temp_file);
	here_doc = open(".here_doc", O_RDONLY);
	use_data()->heredoc_flag = YES;
	free(token);
	return (here_doc);
}

int	contains_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_iswhitespace(str[i]))
			return (YES);
		i++;
	}
	return (NO);
}
