/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:05:02 by gojeda            #+#    #+#             */
/*   Updated: 2025/07/16 17:40:16 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_relative_or_absolute(const char *cmd)
{
	return (cmd[0] == '/'
		|| (ft_strncmp(cmd, "./", 2) == 0)
		|| (ft_strncmp(cmd, "../", 3) == 0));
}

char	*get_cmd(char *cmd, char **envp)
{
	if (is_relative_or_absolute(cmd))
	{
		if (access(cmd, F_OK) == -1)
			return (NULL);
		if (access(cmd, X_OK) == -1)
		{
			ft_putstr_fd("pipex: Permission denied: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
			exit(126);
		}
		return (ft_strdup(cmd));
	}
	return (get_cmd_path(cmd, envp));
}

int	exit_status(t_pipex_status *ps)
{
	if (WIFEXITED(ps->status1))
		ps->status1 = WEXITSTATUS(ps->status1);
	else
		ps->status1 = 1;
	if (WIFEXITED(ps->status2))
		ps->status2 = WEXITSTATUS(ps->status2);
	else
		ps->status2 = 1;
	if (ps->status1 == 127 && ps->status2 == 0)
		ps->final_status = 0;
	else if (ps->status1 == 127)
		ps->final_status = 127;
	else
		ps->final_status = ps->status2;
	return (ps->final_status);
}
