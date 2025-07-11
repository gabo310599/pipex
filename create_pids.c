/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 00:29:51 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/11 18:37:43 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_env_path(char **envp)
{
	char	**paths;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = find_env_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		error_exit("Invalid command");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_split(cmd_args);
		error_exit("Command not found");
	}
	execve(cmd_path, cmd_args, envp);
	free_split(cmd_args);
	error_exit("execve failed");
}

pid_t	create_pid(int fd[2], int pipefd[2], char **argv,
			char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		error_exit("Fork failed");
	if (pid1 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close_all(fd[0], fd[1], pipefd);
		execute_cmd(argv[2], envp);
	}
	return (pid1);
}

pid_t	create_second_pid(int fd[2], int pipefd[2], char **argv,
			char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		error_exit("Fork failed");
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close_all(fd[0], fd[1], pipefd);
		execute_cmd(argv[3], envp);
	}
	return (pid2);
}
