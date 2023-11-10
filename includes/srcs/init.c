# include "../includes/minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->cmd = NULL;
	data->error_flag = 0; //?
	data->heredoc_flag = 0;
	data->quote_flag = 0; //Usefull ?
	data->exstat = 0;
	data->new_env = NULL;	//?cc50396d4ea740724d30bd3221e
	data->line = NULL;
	data->line_cpy = NULL;
	// data->old_attributes;	//? (Is this allocated)
	// data->new_attributes;	//? (Is this allocated)
}
