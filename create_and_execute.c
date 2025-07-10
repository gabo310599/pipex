/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 00:29:51 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/10 01:40:52 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
