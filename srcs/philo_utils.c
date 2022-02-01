/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:43 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/12 23:38:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	memdel(void **pt)
{
	free(*pt);
	*pt = NULL;
}

int	error(int errno, t_world *world)
{
	printf("Error no %d : ", errno);
	if (errno == ARG_ERR)
	{
		printf("arg_error. Programm should be called :\n");
		printf("./philo <nb_philo> <die_t> <eat_t> <sleep_t> <nb_eat(opt)>\n");
		return (errno);
	}
	if (errno == MALLOC_ERR)
		printf("malloc_error\n");
	clear_world(world);
	return (errno);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

long long	get_utime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec);
}
