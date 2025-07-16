/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:35 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/16 16:54:34 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>

# define ARGC_ERROR "Uso: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct s_pipex_status
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
	int		final_status;
}	t_pipex_status;
/* ************************************************************************** */
//UTILS
void	error_exit(char *msg, bool use_perror, int exit_code);
bool	open_files_and_pipes(int *infile, int *outfile,
			char **argv, int pipefd[2]);
void	close_all(int infile, int outfile, int pipefd[2]);
void	free_split(char **split);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
char	**ft_split_cmd(const char *s);
bool	is_relative_or_absolute(const char *cmd);
char	*get_cmd(char *cmd, char **envp);
int		exit_status(t_pipex_status *ps);
/* ************************************************************************** */

/* ************************************************************************** */
//CMD
pid_t	create_pid(int fd[2], int pipefd[2], char **argv,
			char **envp);
pid_t	create_second_pid(int fd[2], int pipefd[2], char **argv,
			char **envp);
void	execute_cmd(char *cmd, char **envp);
char	*get_cmd_path(char *cmd, char **envp);
/* ************************************************************************** */
#endif