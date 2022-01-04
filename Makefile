# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 00:43:59 by bgoncalv          #+#    #+#              #
#    Updated: 2022/01/04 00:46:02 by bgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
FLAGS		= -Wall -Wextra -Werror

NAME 		= philo

SRCS 	=	philo.c philo_utils.c

OBJS = $(SRCS:.c=.o)

_BLUE=\e[34m
_PURPLE=\e[35m
_END=\e[0m

$(NAME):	
			@gcc $(FLAGS) $(SRCS) -o $(NAME) 
			@printf "philo		[$(_BLUE)✓$(_END)]\n"

all : 		$(NAME)

re:			clean
			$(MAKE) $(NAME)

clean :
			@rm -rf $(NAME)
			@printf "$(_PURPLE)philo	deleted$(_END)\n"

fclean :	clean

PHONY : re all clean fclean