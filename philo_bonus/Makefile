# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 00:43:59 by bgoncalv          #+#    #+#              #
#    Updated: 2022/02/06 01:48:23 by bgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
# FLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes/
NAME 		= philo

SRCS 	=	$(wildcard srcs/*.c)

OBJS = $(SRCS:c=o)

_BLUE=\e[34m
_PURPLE=\e[35m
_END=\e[0m

%.o : %.c
			@printf "$(_BLUE)Compiling $< $(_END)\n" $@
			@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
			@printf "philo		[$(_BLUE)✓$(_END)]\n"

all : 		$(NAME)

re:			fclean
			@$(MAKE) $(NAME)

clean :
			@printf "$(_PURPLE)Cleaning philo objects... $(_END)\n" $@
			@rm -rf $(OBJS)


fclean :	clean
			@rm -rf $(NAME)
			@printf "$(_PURPLE)philo	deleted$(_END)\n"

debug :		
			@$(CC) $(FLAGS) $(INCLUDES) -g3 $(SRCS) -o philodebug

PHONY : re all clean fclean