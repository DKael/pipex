/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:49:05 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:48:13 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc1(t_px *px)
{
	int		fd;
	char	*paste_nl;

	fd = open(HEREDOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		parent_end(px);
		err_msg(HEREDOC_NAME, 1, 0);
	}
	paste_nl = ft_strjoin(px->argv[2], "\n");
	if (paste_nl == T_NULL)
	{
		close(fd);
		unlink(HEREDOC_NAME);
		parent_end(px);
		err_msg("malloc", 1, 12);
	}
	here_doc2(fd, paste_nl);
}

void	here_doc2(int fd, char *paste_nl)
{
	char	*buffer;

	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (buffer == T_NULL
			|| ft_strcmp(buffer, paste_nl) == 0)
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	free(paste_nl);
	close(fd);
}
