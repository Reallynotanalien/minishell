
#include "../includes/minishell.h"
//intended to avoid conflicts (to be moved later)

//Removes whitespaces before and after a string.
char	*ft_strtrim_whitespaces(char *str)
{
	int		i_start;
	int		i_end;
	char	*str_cpy;

	i_start = 0;
	while (str[i_start] && (ft_iswhitespace(str[i_start])
			|| !ft_isascii(str[i_start])))
		i_start++;
	i_end = ft_strlen(str) - 1;
	while (str[i_end] && (ft_iswhitespace(str[i_end])
			|| !ft_isascii(str[i_end])))
		i_end--;
	str_cpy = ft_substr(str, i_start, i_end - i_start + 1);
	free (str);
	return (str_cpy);
}
