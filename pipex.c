/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:26 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/11 18:39:54 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_putstr_fd(ARGC_ERROR, 2), 1);
	open_files_and_pipes(&fd[0], &fd[1], argv, pipefd);
	pid1 = create_pid(fd, pipefd, argv, envp);
	pid2 = create_second_pid(fd, pipefd, argv, envp);
	close_all(fd[0], fd[1], pipefd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
