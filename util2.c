/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:59:44 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:52:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (px->file >= 0)
		close(px->file);
	close(px->pp[1][0]);
	close(px->pp[1][1]);
}
