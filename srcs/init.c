/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 14:45:00 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_world *world)
{
	int		i;

	i = -1;
	while (++i < world->nb_philo)
	{
		world->philo[i].id = i + 1;
		world->philo[i].eat_count = 0;
		world->philo[i].last_meal = get_timestamp();
		world->philo[i].lfork = &world->fork[i];
		world->philo[i].rfork = &world->fork[i + 1 % world->nb_philo];
		world->philo[i].world = world;
		if (pthread_mutex_init(&world->fork[i], NULL))
			return (error(MUTEX_ERR, world));
	}
	return (NO_ERR);
}

int	init_world(t_world *world, int argc, char **argv)
{
	world->philo = NULL;
	world->fork = NULL;
	world->nb_philo = atoi(argv[1]);
	world->die_time = (long long) atoi(argv[2]);
	world->eat_time = (long long) atoi(argv[3]);
	world->sleep_time = (long long) atoi(argv[4]);
	if (world->nb_philo < 1 || world->die_time < 1 || world->eat_time < 1
		|| world->sleep_time < 1)
		return (FARGS_ERR);
	world->all_alive = 1;
	world->all_eat = 0;
	world->nb_eat = 0;
	if (argc == 6)
		world->nb_eat = atoi(argv[5]);
	if (world->nb_eat < 0)
		return (FARGS_ERR);
	world->philo = malloc(sizeof(t_philo) * world->nb_philo);
	world->fork = malloc(sizeof(pthread_mutex_t) * world->nb_philo);
	if (!world->fork || !world->philo)
		return (error(MALLOC_ERR, world));
	if (pthread_mutex_init(&world->writing, NULL))
		return (error(MUTEX_ERR, world));
	return (init_philo(world));
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
				pthread_mutex_lock(&world->writing);
				world->all_alive = 0;
				printf("%lld ms %d has died\n",
					get_timestamp() - world->t0, philo->id);
				pthread_mutex_unlock(&world->writing);
				return ;
			}
		}
		usleep(UFREQ);
	}
}

int	start_world(t_world *world)
{
	int		i;
	t_philo	*philo;

	philo = world->philo;
	world->t0 = get_timestamp();
	i = -1;
	while (++i < world->nb_philo)
		if (pthread_create(&philo[i].trd, NULL, philo_life, &philo[i]))
			return (TRD_ERR);
	death_comming(world);
	i = -1;
	while (++i < world->nb_philo)
		if (pthread_join(philo[i].trd, NULL))
			return (TRD_JOIN_ERR);
	i = -1;
	while (++i < world->nb_philo)
		if (pthread_mutex_destroy(&world->fork[i]))
			return (MUTEX_DSTR_ERR);
	if (pthread_mutex_destroy(&world->writing))
		return (MUTEX_DSTR_ERR);
	return (NO_ERR);
}
