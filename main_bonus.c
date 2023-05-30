/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:26 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:48:03 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_px	px;
	int		idx;

	px_init(&px, argc, argv, envp);
	px.path = get_path(envp);
	px.pp = (int **)ft_calloc(px.cmd_num + 2, sizeof(int *));
	if (px.pp == T_NULL)
	{
		parent_end(&px);
		err_msg("malloc", 1, 12);
	}
	idx = -1;
	while (++idx <= px.cmd_num)
	{
		px.pp[idx] = (int *)malloc(sizeof(int) * 2);
		if (px.pp[idx] == T_NULL)
		{
			parent_end(&px);
			err_msg("malloc", 1, 12);
		}
	}
	pipex1(&px);
}

void	pipex1(t_px *px)
{
	int	idx;

	idx = 0;
	while (++idx < px->cmd_num)
	{
		if (pipe(px->pp[idx]) == -1)
		{
			while (--idx >= 1)
			{
				close(px->pp[idx][0]);
				close(px->pp[idx][1]);
			}
			parent_end(px);
			err_msg(T_NULL, 1, 32);
		}
	}
	px->pp[px->cmd_num + 1] = T_NULL;
	if (px->heredoc_flag == 1)
		here_doc1(px);
	pipex2(px);
}

void	pipex2(t_px *px)
{
	int	idx;

	idx = -1;
	while (++idx < px->cmd_num)
	{
		px->last_pid = fork();
		if (px->last_pid == -1)
		{
			while (--idx >= 0)
				wait(T_NULL);
			close_pipes(px);
			parent_end(px);
			err_msg(T_NULL, 1, 0);
		}
		else if (px->last_pid == 0)
			child1(px, idx);
	}
	pipex3(px);
}

void	pipex3(t_px *px)
{
	int	idx;
	int	exit_code;

	close_pipes(px);
	idx = -1;
	while (++idx < px->cmd_num)
	{
		if (px->last_pid == wait(&px->wstatus))
			exit_code = (px->wstatus >> 8) & 0xFF;
	}
	parent_end(px);
	exit(exit_code);
}

void	parent_end(t_px *px)
{
	if (px->heredoc_flag == 1 && access(HEREDOC_NAME, F_OK) == 0)
		unlink(HEREDOC_NAME);
	free_2d_array((void **)px->pp);
	free_2d_array((void **)px->path);
}
