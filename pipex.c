/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:26 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/16 16:48:31 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int				pipefd[2];
	int				fd[2];
	t_pipex_status	ps;

	if (argc != 5)
		return (ft_putstr_fd(ARGC_ERROR, 2), 1);
	open_files_and_pipes(&fd[0], &fd[1], argv, pipefd);
	ps.pid1 = create_pid(fd, pipefd, argv, envp);
	waitpid(ps.pid1, &ps.status1, 0);
	ps.pid2 = create_second_pid(fd, pipefd, argv, envp);
	close_all(fd[0], fd[1], pipefd);
	waitpid(ps.pid2, &ps.status2, 0);
	return (exit_status(&ps));
}
