# include "../../includes/minishell.h"

char	*access_path(t_command *cmd, char **path_env)
{
	int		i;
	char	*path_join;

	i = 0;
	while (path_env[i])
	{
		path_join = ft_strjoin(path_env[i], "/");
		cmd->path = ft_strjoin (path_join, cmd->cmd[0]);
		free(path_join);
		if (access(cmd->path, F_OK) == 0)
			return (cmd->path);
		free(cmd->path);
		cmd->path = NULL;
		i++;
	}
	return (NULL);
}

/*Looks through the environment to find an executable path for the command sent
as an argument.*/
char	*find_path(t_command **cmd, char **env)
{
	int		i;
	char	**path_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
		if (env[i] == NULL || env[i + 1] == NULL)
			return (FIND_PATH_ERROR);
	}
	path_env = (char **)ft_split(env[i] + 5, ':');
	i = 0;
	(*cmd)->path = access_path(*cmd, path_env);
	return ((*cmd)->path);
}

t_command	*find_cmd(t_command **cmd)
{
	(*cmd)->path = find_path(cmd, use_data()->new_env);
	if ((*cmd)->path == NULL
		|| ft_strncmp(FIND_PATH_ERROR, (*cmd)->path, 43) == 0)
	{
		printf("COULD NOT FIND PATH\n");
	}
	return (*cmd);
}

void	get_path(t_command *cmd)
{
	if (access(cmd->cmd[0], F_OK) == 0)
	{
		cmd->path = cmd->cmd[0];
		printf("is an absolute path\n");
	}
	else if (cmd->builtin_flag == YES)
		printf("is a builtin)\n");
	else
		find_cmd(&cmd);
}
