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
	}
	waitpid((*cmd)->pid, NULL, 0);
}

void	child(t_command **cmd, char **env)
{
	close((*cmd)->fd[0]);
	close((*cmd)->outfile);
	dup2((*cmd)->fd[1], STDOUT_FILENO);
	close((*cmd)->fd[1]);
	execve((*cmd)->path, (char *const *)(*cmd)->cmd, env);
	exit(0);
}

void	pipex(t_command **cmd, char **env)
{
	if (pipe((*cmd)->fd) < 0)
		printf("PIPE did not work\n");
	(*cmd)->pid = fork();
	if ((*cmd)->pid == -1)
		printf("FORK did not work\n");
	else if ((*cmd)->pid == 0)
		child(cmd, env);
	else
	{
		close((*cmd)->fd[1]);
		dup2((*cmd)->fd[0], STDIN_FILENO);
		close((*cmd)->fd[0]);
	}
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
		execute_one_command(&cmd, use_data()->new_env);
	}
	else
	{
		while (cmd && nb_cmds > 1)
		{
			get_path(cmd);
			pipex(&cmd, use_data()->new_env);
			nb_cmds--;
			if (cmd->next)
				cmd = cmd->next;
		}
		get_path(cmd);
		if (pipe(cmd->fd) < 0)
			printf("PIPE did not work\n");
		cmd->pid = fork();
		if (cmd->pid == -1)
			printf("FORK did not work\n");
		else if (cmd->pid == 0)
		{
			close(cmd->fd[0]);
			close(cmd->fd[1]);
			dup2(cmd->outfile, STDOUT_FILENO);
			close(cmd->outfile);
			execve(cmd->path, (char *const *)cmd->cmd, use_data()->new_env);
		}
		waitpid(cmd->pid, NULL, 0);
	}
}
