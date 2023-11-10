# include "../../../includes/minishell.h"

/*Adds an index number representing the token's type to facilitate
the transfer to the command struct later on. 
1 = T_STR
2 = T_SUBST
3 = T_PIPE
4 = T_HEREDOC
5 = T_INFILE
6 = T_OUTFILE
7 = T_APPEND*/
int	check_type(char *token)
{
	int	type;

	type = 0;
	if (is_redirection(token[0]))
	{
		if (token[0] == '|')
			type = T_PIPE;
		else if (token[0] == '<')
		{
			if (token[1] == '<')
				type = T_HEREDOC;
			else
				type = T_INFILE;
		}
		else if (token[0] == '>')
		{
			if (token[1] == '>')
				type = T_APPEND;
			else
				type = T_OUTFILE;
		}
	}
	else
		type = T_STR;
	return (type);
}

/*Initializes a new token node.*/
t_token	*create_token(void)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/*Adds a new token node to the linked list and places it at the
end of the list. Copies the string sent as an argument in the 
token attribute. Then checks for the token type.*/
t_token	*add_token(char *token)
{
	t_token	*new;
	t_token	*next;

	if (token == NULL)
		return (NULL);
	new = create_token();
	if (!new)
		return (NULL);
	new->token = ft_strdup(token);
	new->type = check_type(token);
	if (use_data()->token == NULL)
	{
		use_data()->token = new;
		use_data()->token->prev = NULL;
	}
	else
	{
		next = use_data()->token;
		while (next->next != NULL)
			next = next->next;
		new->prev = next;
		next->next = new;
	}
	return (use_data()->token);
}

/*If the token linked list is not empty, frees each token one by
one.*/
void	free_tokens_if_not_empty(void)
{
	t_token	*temp;

	if (!use_data()->token)
		return ;
	while (use_data()->token)
	{
		temp = use_data()->token->next;
		free(use_data()->token);
		use_data()->token = temp;
	}
}

/*Returns the adress of the previous token's node or 
NULL if there is no previous token.*/
t_token	*lstget_prev(t_token *lst, t_token *reference)
{
	t_token	*previous;

	while (lst != reference)
	{
		previous = lst;
		lst = lst->next;
	}
	if (previous == lst)
		return (NULL);
	return (previous);
}
