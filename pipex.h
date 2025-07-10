/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:35 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/10 01:36:01 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>

# define ARGC_ERROR "Uso: ./pipex file1 cmd1 cmd2 file2\n"

/* ************************************************************************** */
//UTILS
void	error_exit(const char *msg);
bool	open_files_and_pipes(int *infile, int *outfile,
			char **argv, int pipefd[2]);
void	close_all(int infile, int outfile, int pipefd[2]);
void	free_split(char **split);
/* ************************************************************************** */

/* ************************************************************************** */
//CMD
pid_t	create_pid(int fd[2], int pipefd[2], char **argv,
			char **envp);

/* ************************************************************************** */
#endif