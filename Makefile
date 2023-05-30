# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:30:42 by hyungdki          #+#    #+#              #
#    Updated: 2023/05/30 16:26:01 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c	\
		child.c	\
		util1.c	\
		util2.c	\
		error.c	\
		
OBJS = 	${SRCS:.c=.o}

SRCS_BONUS =	main_bonus.c	\
				child1_bonus.c	\
				child2_bonus.c	\
				util1_bonus.c	\
				util2_bonus.c	\
				error_bonus.c	\
				heredoc_bonus.c	\

OBJS_BONUS = 	${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT_DIR = libft

LIBGNL_DIR = gnl

WITH_BONUS = 0

ifeq ($(WITH_BONUS),1)
	TOTAL_OBJS = ${OBJS_BONUS}
	LDFLAGS = -L./libft -L./gnl -lft -lgnl
else
	TOTAL_OBJS = ${OBJS}
	LDFLAGS = -L./libft -lft
endif

${NAME} : ${TOTAL_OBJS}
		make -C ${LIBFT_DIR} all
ifeq ($(WITH_BONUS),1)
	make -C ${LIBGNL_DIR} all
endif
		${CC} ${CFLAGS} ${LDFLAGS} ${TOTAL_OBJS} -o $@

%.o :%.c
	${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	make -C ${LIBFT_DIR} fclean
	make -C ${LIBGNL_DIR} fclean
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: 
	make clean
	rm -rf ${NAME}

re: 
	make fclean
	make all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re bonus
