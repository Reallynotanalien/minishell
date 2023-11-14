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

void	execute_one_command(t_command **cmd, char **env)
{
	(*cmd)->pid = fork();
	if ((*cmd)->pid == -1)
		printf("FORK did not work\n");
	else if ((*cmd)->pid == 0)
	{
		if ((*cmd)->outfile != STDOUT_FILENO)
		{
			dup2((*cmd)->outfile, STDOUT_FILENO);
			close((*cmd)->outfile);
		}
		execve((*cmd)->path, (char *const *)(*cmd)->cmd, env);
		exit(0);
		printf("Why is it printing, execve should have closed\n");
	}
	waitpid((*cmd)->pid, NULL, 0);
}

void	exec(t_command *cmd)
{
	int	nb_cmds;

	printf("I just added random text here to test the git repo\n");
	nb_cmds = count_commands(cmd);
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (nb_cmds == 1)
	{
		get_path(cmd);
		execute_one_command(&cmd, use_data()->new_env);
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
