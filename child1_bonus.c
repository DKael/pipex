/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:56:50 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:45:37 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child1(t_px *px, int idx)
{
	int	cmd_idx;

	if (idx == 0 || idx == px->cmd_num - 1)
		child_file_open1(px, idx);
	cmd_idx = idx + 2 + px->heredoc_flag;
	px->cmd = ft_split(px->argv[cmd_idx], ' ');
	if (px->cmd == T_NULL)
	{
		child_end(px);
		err_msg("malloc", 1, 12);
	}
	child2(px, idx);
}

void	child2(t_px *px, int idx)
{
	px->cmd_path = get_cmd_path1(px->path, px->cmd[0]);
	if (px->cmd_path == T_NULL && px->path != T_NULL)
	{
		write(2, "pipex: ", 7);
		write(2, px->cmd[0], ft_strlen(px->cmd[0]));
		write(2, ": command not found\n", 21);
		child_end(px);
		exit(127);
	}
	else if (px->cmd_path == T_NULL && px->path == T_NULL)
	{
		write(2, "pipex: ", 7);
		perror(px->cmd[0]);
		child_end(px);
		exit(127);
	}
	child3(px, idx);
}

void	child3(t_px *px, int idx)
{
	if (dup2(px->pp[idx][0], STDIN_FILENO) == -1
		|| dup2(px->pp[idx + 1][1], STDOUT_FILENO) == -1)
	{
		child_end(px);
		err_msg(T_NULL, 1, 0);
	}
	close_pipes(px);
	if (execve(px->cmd_path, px->cmd, px->envp) == -1)
	{
		free_2d_array((void **)px->cmd);
		free(px->cmd_path);
		err_msg(T_NULL, 1, 0);
	}
}
