/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:46:31 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/14 16:09:23 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg, bool use_perror, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	if (use_perror)
		perror(msg);
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(exit_code);
}

bool	open_files_and_pipes(int *infile, int *outfile,
			char **argv, int pipefd[2])
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
	{
		ft_putstr_fd("pipex: ", 2),
		perror(argv[1]);
		*infile = open("/dev/null", O_RDONLY);
		if (*infile < 0)
			error_exit("/dev/null", true, 1);
	}
	*outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		error_exit(argv[4], true, 1);
	if (pipe(pipefd) == -1)
		error_exit("pipe", true, 1);
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

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	total_len = len1 + len2 + len3 + 1;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	ft_strlcat(result, s2, total_len);
	ft_strlcat(result, s3, total_len);
	return (result);
}
