/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:01:18 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:47:29 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_2d_array(void **array)
{
	int	idx;

	if (array != T_NULL)
	{
		idx = -1;
		while (array[++idx] != T_NULL)
			free(array[idx]);
		free(array);
	}
}

void	close_pipes(t_px *px)
{
	int	idx;

	if (px->file >= 3)
		close(px->file);
	if (px->pp != T_NULL)
	{
		idx = 0;
		while (++idx < px->cmd_num)
		{
			if (px->pp[idx] != T_NULL)
			{
				close(px->pp[idx][0]);
				close(px->pp[idx][1]);
			}
		}
	}
}
