/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:56:50 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:50:44 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_px *px, int idx)
{
	if (idx == 0)
		px->file = open(px->argv[1], O_RDONLY);
	else if (idx == 1)
		px->file = open(px->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	px->pp[2 * idx][idx] = px->file;
	if (px->file < 0)
	{
		child_end(px);
		if (idx == 0)
			err_msg(px->argv[1], 1, 0);
		else if (idx == 1)
			err_msg(px->argv[4], 1, 0);
	}
	px->cmd = ft_split(px->argv[2 + idx], ' ');
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

void	child_end(t_px *px)
{
	close_pipes(px);
	free_2d_array((void **)px->cmd);
	free(px->cmd_path);
}
