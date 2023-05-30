/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:27:26 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:51:47 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_px	px;

	if (argc != 5)
		err_msg(T_NULL, 1, 22);
	px_init(&px, argv, envp);
	px.path = get_path(envp);
	if (pipe(px.pp[1]) == -1)
	{
		free_2d_array((void **)px.path);
		err_msg(T_NULL, 1, 32);
	}
	pipex(&px);
}

void	pipex(t_px *px)
{
	int	idx;

	idx = -1;
	while (++idx < 2)
	{
		px->pid[idx] = fork();
		if (px->pid[idx] == -1)
		{
			while (--idx >= 0)
				wait(T_NULL);
			parent_end(px);
			err_msg(T_NULL, 1, 0);
		}
		else if (px->pid[idx] == 0)
			child1(px, idx);
	}
	close_pipes(px);
	waitpid(px->pid[0], T_NULL, 0);
	waitpid(px->pid[1], &(px->wstatus), 0);
	free_2d_array((void **)px->path);
	exit((px->wstatus >> 8) & 0xFF);
}

void	parent_end(t_px *px)
{
	close_pipes(px);
	free_2d_array((void **)px->path);
}
