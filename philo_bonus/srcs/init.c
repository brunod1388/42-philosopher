/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/08 04:39:47 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_semaphore(t_world *world)
{
	sem_unlink(FORKSEM);
	sem_unlink(WRITESEM);
	sem_unlink(EATSEM);
	sem_unlink(DEATHSEM);
	world->forks = sem_open(FORKSEM, O_CREAT, S_IRWXU, world->nb_philo);
	world->writing = sem_open(WRITESEM, O_CREAT, S_IRWXU, 1);
	world->full_eat = sem_open(EATSEM, O_CREAT, S_IRWXU, 0);
	world->death = sem_open(DEATHSEM, O_CREAT, S_IRWXU, 0);
}

static void	init_philo(t_world *world)
{
	int	i;

	i = 0;
	while (i < world->nb_philo)
	{
		world->philo[i].id = i + 1;
		world->philo[i].eat_count = 0;
		world->philo[i].world = world;
		i++;
	}
}

int	init_world(t_world *world, int argc, char **argv)
{
	world->philo = NULL;
	world->nb_philo = atoi(argv[1]);
	world->die_time = (long long) atoi(argv[2]);
	world->eat_time = (long long) atoi(argv[3]);
	world->sleep_time = (long long) atoi(argv[4]);
	if (world->nb_philo < 1 || world->die_time < 1 || world->eat_time < 1
		|| world->sleep_time < 1)
		return (FARGS_ERR);
	world->philo = malloc(sizeof(t_philo) * world->nb_philo);
	if (!world->philo)
		return (MALLOC_ERR);
	world->all_eat = 0;
	world->all_alive = 1;
	world->nb_eat = -1;
	if (argc == 6)
		world->nb_eat = atoi(argv[5]);
	if (argc == 6 && world->nb_eat < -1)
		return (FARGS_ERR);
	init_philo(world);
	init_semaphore(world);
	return (NO_ERR);
}
