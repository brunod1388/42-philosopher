/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:43 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/08 04:35:15 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *p, char *s)
{
	long long	time;

	sem_wait(p->world->writing);
	time = get_timestamp() - p->world->t0;
	printf("%lld ms %d %s\n", time, p->id, s);
	sem_post(p->world->writing);
}

void	*check_eat(void *world)
{
	int		i;
	t_world	*w;

	w = (t_world *) world;
	i = 0;
	while (i++ < w->nb_philo)
		sem_wait(w->full_eat);
	w->all_eat = 1;
	return (NULL);
}

void	*check_death(void *world)
{
	t_world	*w;

	w = (t_world *) world;
	sem_wait(w->death);
	w->all_alive = 0;
	return (NULL);
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
	if (errno == FORK_ERR)
		printf("fork_error\n");
	if (errno == SEM_ERR)
		printf("semaphore_error\n");
	if (world->philo)
		free(world->philo);
	return (errno);
}

long long	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
