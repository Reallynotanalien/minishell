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

void	child_one(t_command *cmd, char **env)
{
	dup2(cmd->outfile, STDOUT_FILENO);
	// close(cmd->fd[1]);
	execve(cmd->path, (char *const *)cmd->cmd[0], env);
}

void	pipex(t_command *cmd)
{
	int	pid;

	printf("I am in pipex\n");
	pid = fork();
	if (pid == -1)
		printf("FORK DID NOT WORK\n");
	else if (pid == 0)
	{
		child_one(cmd, use_data()->new_env);
		printf("Hi I got here\n");
	}
	else
	{
		printf("PID is not 0??\n");
		// close(cmd->fd[1]);
		// dup2(cmd->next->fd[0], STDIN_FILENO);
		// close(cmd->fd[0]);
	}
	// waitpid(pid, NULL, 0);
}

void	child_test(t_command *cmd)
{
	//needs to solve the cat problem with the prompt
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("FORK DID NOT WORK\n");
	else if (pid == 0)
		execve(cmd->path, (char *const *)cmd->cmd, use_data()->new_env);
	waitpid(pid, NULL, 0);
}

void	child_two(t_command *cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("PIPE DID NOT WORK\n");
	else if (pid == 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		execve(cmd->path, (char *const *)cmd->cmd[0], env);
	}
	waitpid(pid, NULL, 0);
}

void	exec(t_command *cmd)
{
	int	nb_cmds;

	nb_cmds = count_commands(cmd);
	// dup2(cmd->infile, STDIN_FILENO);
	// if (nb_cmds == 1)
	// {
	// 	get_path(cmd);
	// 	child_test(cmd);
	// }
	// else
	// {
	// 	while (cmd && nb_cmds > 1)
	// 	{
	// 		get_path(cmd);
	// 		pipex(cmd);
	// 		nb_cmds--;
	// 		if (cmd->next)
	// 			cmd = cmd->next;
	// 		else
	// 			break ;
	// 	}
	// 	get_path(cmd);
	// child_two(cmd, use_data()->new_env);
	// }
}
