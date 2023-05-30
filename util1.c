/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:01:26 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:51:23 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	*path;
	char	**result;
	int		idx;

	if (envp != T_NULL)
	{
		idx = -1;
		while (envp[++idx] != T_NULL)
		{
			if (ft_strncmp("PATH=", envp[idx], 5) == 0)
			{
				path = &envp[idx][5];
				result = ft_split(path, ':');
				if (result == T_NULL)
					err_msg("malloc", 1, 12);
				return (result);
			}
		}
	}
	return (T_NULL);
}

char	*get_cmd_path1(char **path, char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (path == T_NULL)
		return (T_NULL);
	return (get_cmd_path2(path, cmd));
}

char	*get_cmd_path2(char **path, char *cmd)
{
	int		idx;
	char	*slash_cmd;
	char	*tmp_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	if (slash_cmd == T_NULL)
		err_msg("malloc", 1, 12);
	idx = -1;
	while (path[++idx])
	{
		tmp_cmd = ft_strjoin(path[idx], slash_cmd);
		if (tmp_cmd == T_NULL)
			err_msg("malloc", 1, 12);
		if (access(tmp_cmd, X_OK) == 0)
		{
			free(slash_cmd);
			return (tmp_cmd);
		}
		free(tmp_cmd);
	}
	free(slash_cmd);
	return (T_NULL);
}

void	px_init(t_px *px, char **argv, char **envp)
{
	px->file = -1;
	px->argv = argv;
	px->envp = envp;
	px->path = T_NULL;
	px->cmd = T_NULL;
	px->cmd_path = T_NULL;
	px->wstatus = 0;
}
