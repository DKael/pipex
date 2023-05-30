/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:56:03 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 16:48:41 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define HEREDOC_NAME "heredoc_tmp"
# define T_NULL (void *)0

typedef struct s_px
{
	int		heredoc_flag;
	int		file;
	int		argc;
	int		cmd_num;
	char	**argv;
	char	**envp;
	int		**pp;
	char	**path;
	char	**cmd;
	char	*cmd_path;
	pid_t	last_pid;
	int		wstatus;
}	t_px;

char	**get_path(char **envp);
char	*get_cmd_path1(char **path, char *cmd);
char	*get_cmd_path2(char **path, char *cmd);
void	px_init(t_px *px, int argc, char **argv, char **envp);
void	free_2d_array(void **array);
void	close_pipes(t_px *px);
void	err_msg(char *msg, int exit_code, int uerrno);
void	pipex1(t_px *px);
void	pipex2(t_px *px);
void	pipex3(t_px *px);
void	parent_end(t_px *px);
void	child1(t_px *px, int idx);
void	child2(t_px *px, int idx);
void	child3(t_px *px, int idx);
void	child_file_open1(t_px *px, int idx);
void	child_file_open2(t_px *px, int idx);
void	child_end(t_px *px);
void	here_doc1(t_px *px);
void	here_doc2(int fd, char *paste_nl);

#endif