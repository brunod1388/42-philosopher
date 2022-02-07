/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:25:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/06 02:07:05 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sleapt(t_philo *p, long long time)
{
	long long	tstart;

	tstart = get_timestamp();
	while (p->world->all_alive && !p->world->all_eat
		&& get_timestamp() - tstart < time)
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
	sleapt(p, p->world->eat_time);
	++p->eat_count;
	sem_post(p->world->forks);
	sem_post(p->world->forks);
}

static int	check_eat(t_world *w)
{
	int	i;

	if (!w->nb_eat)
		return (0);
	i = 0;
	while (i < w->nb_philo)
		if (w->philo[i++].eat_count < w->nb_eat)
			return (0);
	w->all_eat = 1;
	return (1);
}

static void	*death_comming(void *philosopher)
{
	t_philo	*philo;
	t_world	*world;

	philo = (t_philo *) philosopher;
	world = philo->world;
	while (world->all_alive && !world->all_eat)
	{
		if (get_timestamp() - philo->last_meal > world->die_time)
		{
			world->all_alive = 0;
			sem_wait(world->writing);
			printf("%lld ms ", get_timestamp() - world->t0);
			printf("%d has died\n", philo->id);
			sem_post(world->writing);
			break;
		}
		usleep(UFREQ);
	}
	printf("fin philo %d\n", philo->id);
	return (NULL);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	if (p->id % 2)
		usleep(50);
	p->last_meal = get_timestamp();
	if (pthread_create(&p->the_death, NULL, death_comming, philo))
		exit(EXIT_FAILURE);
	while (p->world->all_alive && !p->world->all_eat)
	{
		philo_eat(p);
		if (check_eat(p->world))
			break ;
		print_state(p, "is sleeping");
		sleapt(p, p->world->sleep_time);
		print_state(p, "is thinking");
	}
	pthread_join(p->the_death, NULL);
	exit(EXIT_SUCCESS);
}
