/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 03:39:28 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_world *world)
{
	int		i;
	int		nbphi;

	i = -1;
	nbphi = world->nb_philo;
	while (++i < nbphi)
	{
		world->philo[i].id = i + 1;
		world->philo[i].eat_count = 0;
		world->philo[i].last_meal = get_timestamp();
		world->philo[i].lfork = &world->fork[i];
		world->philo[i].rfork = &world->fork[i + 1 % nbphi];
		world->philo[i].world = world;
		if (pthread_mutex_init(&world->fork[i], NULL))
			return (error(MUTEX_ERR, world));
	}
	return (NO_ERR);
}

int	init_world(t_world *world, int argc, char **argv)
{
	world->nb_philo = atoi(argv[1]);
	world->die_time = (long long) atoi(argv[2]);
	world->eat_time = (long long) atoi(argv[3]);
	world->sleep_time = (long long) atoi(argv[4]);
	world->all_alive = 1;
	world->all_eat = 0;
	world->philo = NULL;
	world->fork = NULL;
	if (argc == 6)
		world->nb_eat = atoi(argv[5]);
	else
		world->nb_eat = 0;
	world->philo = malloc(sizeof(t_philo) * world->nb_philo);
	world->fork = malloc(sizeof(pthread_mutex_t) * world->nb_philo);
	if (!world->fork || !world->philo)
		return (error(MALLOC_ERR, world));
	if (pthread_mutex_init(&world->writing, NULL))
		return (error(MUTEX_ERR, world));
	return (init_philo(world));
}

void	clear_world(t_world *world)
{
	if (world->philo)
		memdel((void **) &world->philo);
	if (world->fork)
		memdel((void **) &world->fork);
}

static void	death_comming(t_world *world)
{
	int		i;
	t_philo	*philo;

	while (world->all_alive)
	{
		i = -1;
		while (++i < world->nb_philo)
		{
			philo = &world->philo[i];
			if (get_timestamp() - philo->last_meal > world->die_time)
			{
				print_state(philo, "died");
				world->all_alive = 0;
				return ;
			}
		}
		usleep(UFREQ);
	}
}

void	start_world(t_world *world)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = world->philo;
	world->t0 = get_timestamp();
	while (++i < world->nb_philo)
		pthread_create(&philo[i].trd, NULL, philo_life, &philo[i]);
	death_comming(world);
	i = -1;
	while (++i < world->nb_philo)
		pthread_join(philo[i].trd, NULL);
	i = -1;
	while (++i < world->nb_philo)
		pthread_mutex_destroy(&world->fork[i]);
	pthread_mutex_destroy(&world->writing);
}
