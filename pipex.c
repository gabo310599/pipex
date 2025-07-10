/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:26 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/10 01:38:57 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	int	fd[2];

	if (argc != 5)
		return (ft_putstr_fd(ARGC_ERROR, 2), 1);
	open_files_and_pipes(&fd[0], &fd[1], argv, pipefd);
	create_pid(fd, pipefd, argv, envp);
	close_all(fd[0], fd[1], pipefd);
	return (0);
}
