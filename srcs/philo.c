/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/12 22:26:22 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_world(t_world *world, int argc, char **argv)
{
	world->nb_philo = atoi(argv[1]);
	world->die_time = atoi(argv[2]);
	world->eat_time = atoi(argv[3]);
	world->sleep_time = atoi(argv[4]);
	world->philo = NULL;
	world->fork = NULL;
	if (argc == 6)
		world->nb_eat = atoi(argv[5]);
	else
		world->nb_eat = 0;
	world->philo = malloc(sizeof(pthread_t) * world->nb_philo);
	world->fork = malloc(sizeof(pthread_mutex_t) * world->nb_philo);
	if (!world->fork || !world->nb_philo)
		return (error(MALLOC_ERR, world));
	return (NO_ERR);
}

void	clear_world(t_world *world)
{
	if (world->philo)
		memdel((void **)&world->philo);
	if (world->fork)
		memdel((void **)&world->fork);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	while (p->state != DEAD)
	{
		if (p->state == THINKING)
			philo_tryeat(p);
		else if (p->state == EATING)
			philo_gosleep(p);
		else if (p->state == SLEEPING)
			philo_sleep(p);
		if (philo->state == SLEEPING && check_eat(p->world))
			break ;
	}
	return (NULL);
}

void	init_philo(t_world *world)
{
	int	i;
	int	nbphi;

	i = 0;
	nbphi = world->nb_philo;
	world->t0 = get_timestamp();
	while (++i <= nbphi)
	{
		world->philo[i].id = i;
		world->philo[i].state = THINKING;
		world->philo[i].count = 0;
		world->philo[i].last_meal_time = get_timestamp();
		world->philo[i].lfork = &world->fork[i - 1];
		world->philo[i].rfork = &world->fork[i % nbphi];
		world->philo[i].world = world;
	}
	i = -1;
	while (++i < nbphi)
	{
		pthread_create(&world->philo[i].trd, NULL,
			philo_life, &world->philo[i]);
		pthread_join(world->philo[i].trd, NULL);
	}
}
