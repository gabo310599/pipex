/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:46:31 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/10 01:19:47 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

bool	open_files_and_pipes(int *infile, int *outfile,
			char **argv, int pipefd[2])
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
		error_exit("Error opening infile");
	*outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		error_exit("Error opening outfile");
	if (pipe(pipefd) == -1)
		error_exit("Pipe failed");
	return (true);
}

void	close_all(int infile, int outfile, int pipefd[2])
{
	close(infile);
	close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
