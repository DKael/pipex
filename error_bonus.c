/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:21:09 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:47:14 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	err_msg(char *msg, int exit_code, int uerrno)
{
	char	*errno_msg;

	if (msg != T_NULL && uerrno != 0)
	{
		write(2, "pipex: ", 7);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		errno_msg = strerror(uerrno);
		write(2, errno_msg, ft_strlen(errno_msg));
	}
	else if (msg == T_NULL && uerrno != 0)
	{
		write(2, "pipex: ", 7);
		errno_msg = strerror(uerrno);
		write(2, errno_msg, ft_strlen(errno_msg));
	}
	else if (msg != T_NULL && uerrno == 0)
	{
		write(2, "pipex: ", 7);
		perror(msg);
	}
	else
		perror("pipex");
	exit(exit_code);
}
