/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:25:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/08 04:44:37 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleapt(long long time)
{
	long long	tstart;

	tstart = get_timestamp();
	while (get_timestamp() - tstart < time)
		usleep(UFREQ);
}

static void	philo_eat(t_philo *p)
{
	sem_wait(p->world->forks);
	print_state(p, "has taken a fork");
	sem_wait(p->world->forks);
	print_state(p, "has taken a fork");
	p->last_meal = get_timestamp();
	print_state(p, "is eating");
	sleapt(p->world->eat_time);
	++p->eat_count;
	sem_post(p->world->forks);
	sem_post(p->world->forks);
}

static void	*death_comming(void *philosopher)
{
	t_philo	*philo;
	t_world	*world;

	philo = (t_philo *) philosopher;
	world = philo->world;
	while (42)
	{
		if (get_timestamp() - philo->last_meal > world->die_time)
		{
			sem_wait(world->writing);
			printf("%lld ms ", get_timestamp() - world->t0);
			printf("%d has died\n", philo->id);
			sem_post(world->death);
			exit(EXIT_SUCCESS);
		}
		usleep(UFREQ);
	}
	return (NULL);
}

void	philo_life(t_philo *p)
{
	p->last_meal = get_timestamp();
	if (p->id % 2)
		usleep(UFREQ);
	if (pthread_create(&p->the_death, NULL, death_comming, p))
		exit(EXIT_FAILURE);
	while (42)
	{
		philo_eat(p);
		if (p->world->nb_eat != -1 && p->eat_count == p->world->nb_eat)
			sem_post(p->world->full_eat);
		print_state(p, "is sleeping");
		sleapt(p->world->sleep_time);
		print_state(p, "is thinking");
	}
}
