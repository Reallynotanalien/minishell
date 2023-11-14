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

void	child_two(t_command **cmd)
{
	if (pipe(use_data()->fd) < 0)
		printf("PIPE did not work\n");
	use_data()->pid = fork();
	if (use_data()->pid == -1)
		printf("FORK did not work\n");
	else if (use_data()->pid == 0)
	{
		use_data()->child = YES;
		close(use_data()->fd[0]);
		close(use_data()->fd[1]);
		if ((*cmd)->outfile != STDOUT_FILENO)
		{
			dup2((*cmd)->outfile, STDOUT_FILENO);
			close((*cmd)->outfile);
		}
		execve((*cmd)->path, (*cmd)->cmd, use_data()->new_env);
	}
	else
	{
		use_data()->child = NO;
		close(use_data()->fd[0]);
		close(use_data()->fd[1]);
		waitpid(use_data()->pid, NULL, 0);
	}
}

void	child_one(t_command **cmd)
{
	use_data()->child = YES;
	close(use_data()->fd[0]);
	close((*cmd)->outfile);
	dup2(use_data()->fd[1], STDOUT_FILENO);
	close(use_data()->fd[1]);
	execve((*cmd)->path, (*cmd)->cmd, use_data()->new_env);
}

void	pipex(t_command **cmd)
{
	if ((*cmd)->infile != STDIN_FILENO)
	{
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
	}
	if (pipe(use_data()->fd) < 0)
		printf("PIPE did not work\n");
	use_data()->pid = fork();
	if (use_data()->pid == -1)
		printf("FORK did not work\n");
	else if (use_data()->pid == 0)
		child_one(cmd);
	else
	{
		use_data()->child = NO;
		close(use_data()->fd[1]);
		(*cmd)->next->infile = use_data()->fd[0];
		close(use_data()->fd[0]);
	}
}

void	exec(t_command *cmd)
{
	int	nb_cmds;

	nb_cmds = count_commands(cmd);
	while (cmd && nb_cmds > 1)
	{
		get_path(cmd);
		if (ft_strcmp(cmd->cmd[0], "cat") == 0)
			signal(SIGINT, cat_handler);
		pipex(&cmd);
		nb_cmds--;
		if (cmd->next)
			cmd = cmd->next;
	}
	get_path(cmd);
	if (ft_strcmp(cmd->cmd[0], "cat") == 0)
		signal(SIGINT, cat_handler);
	child_two(&cmd);
}
