/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:43 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 14:23:41 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *p, char *s)
{
	long long	time;

	time = get_timestamp() - p->world->t0;
	pthread_mutex_lock(&p->world->writing);
	if (p->world->all_alive && !p->world->all_eat)
		printf("%lld ms %d %s\n", time, p->id, s);
	pthread_mutex_unlock(&p->world->writing);
}

static void	clear_world(t_world *world)
{
	if (world->philo)
		free(world->philo);
	if (world->fork)
		free(world->fork);
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
	if (errno == FARGS_ERR)
		printf("farg_eror. Args has to be positive integer.\n");
	if (errno == MUTEX_ERR)
		printf("mutex_error\n");
	if (errno == TRD_ERR)
		printf("thread_create_error\n");
	if (errno == TRD_JOIN_ERR)
		printf("thread_join_error\n");
	if (errno == MUTEX_DSTR_ERR)
		printf("mutex_destroy_error\n");
	clear_world(world);
	return (errno);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
