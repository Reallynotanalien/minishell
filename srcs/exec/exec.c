# include "../../includes/minishell.h"

int	count_commands(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->next)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	exec(t_command *cmd)
{
	int	nb_cmds;

	nb_cmds = count_commands(cmd);
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (nb_cmds == 1)
	{
		get_path(cmd);
		printf("Only one command to execute\n");
	}
	else
	{
		while (cmd && nb_cmds > 1)
		{
			get_path(cmd);
			printf("Do pipex\n");
			nb_cmds--;
			if (cmd->next)
				cmd = cmd->next;
			else
				break ;
		}
		get_path(cmd);
		printf("Execute last command\n");
	}
}
