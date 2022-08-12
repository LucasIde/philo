# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 15:04:58 by lide              #+#    #+#              #
#    Updated: 2022/08/12 19:14:23 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/philo.c\
			srcs/utils.c\
			srcs/value.c\
			srcs/init.c\
			srcs/free.c\
			srcs/death_timer.c

NAME	=	philo.a
EXEC	=	philo
OBJS	=	${SRCS:.c=.o}
CC		=	@gcc
CFLAGS	=	-Wall -Wextra -Werror

${NAME}:	${OBJS}
			@ar -rc ${NAME} ${OBJS}
			@${CC} ${CFLAGS} ${NAME} -o ${EXEC}
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
