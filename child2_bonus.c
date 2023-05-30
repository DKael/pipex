/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:00:40 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:49:56 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_file_open1(t_px *px, int idx)
{
	if (idx == 0)
	{
		if (px->heredoc_flag == 1)
			px->file = open(HEREDOC_NAME, O_RDONLY);
		else
			px->file = open(px->argv[1], O_RDONLY);
	}
	else if (idx == px->cmd_num - 1)
	{
		if (px->heredoc_flag == 1)
			px->file = open(px->argv[px->argc - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			px->file = open(px->argv[px->argc - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	child_file_open2(px, idx);
}

void	child_file_open2(t_px *px, int idx)
{
	if (px->file < 0)
	{
		child_end(px);
		if (idx == 0)
			err_msg(px->argv[1], 1, 0);
		else if (idx == px->cmd_num - 1)
			err_msg(px->argv[px->argc - 1], 1, 0);
	}
	if (idx == 0)
		px->pp[0][0] = px->file;
	else if (idx == px->cmd_num - 1)
		px->pp[px->cmd_num][1] = px->file;
}

void	child_end(t_px *px)
{
	close_pipes(px);
	free_2d_array((void **)px->cmd);
	free(px->cmd_path);
}
