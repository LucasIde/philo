# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 15:04:58 by lide              #+#    #+#              #
#    Updated: 2022/08/08 07:17:31 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/philo.c\
			srcs/utils.c\
			srcs/value.c

NAME	=	minishell.a
EXEC	=	minishell
OBJS	=	${SRCS:.c=.o}
CC		=	@gcc
CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include

${NAME}:	${OBJS}
			@ar -rc ${NAME} ${OBJS}
			@${CC} ${CFLAGS} ${NAME} ${EXEC}
			@echo "|philosophers: ready to use|"

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@echo "-everything as been Cleaned-"

fclean:
			@rm -f ${OBJS}
			@rm -f ${NAME} ${EXEC}
			@echo "-everything as been Fcleaned-"

re:			fclean all

.PHONY: all clean fclean re
