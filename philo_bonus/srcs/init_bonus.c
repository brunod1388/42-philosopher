/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/06 02:10:33 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_philo(t_world *world)
{
	int		i;

	i = 0;
	while (i < world->nb_philo)
	{
		world->philo[i].id = i + 1;
		world->philo[i].eat_count = 0;
		world->philo[i].last_meal = get_timestamp();
		world->philo[i].world = world;
		++i;
	}
	return (NO_ERR);
}

static void	init_semaphore(t_world *world)
{
	sem_unlink(FORKSEM);
	sem_unlink(WRITESEM);
	world->forks = sem_open(FORKSEM, O_CREAT, S_IRWXU, world->nb_philo);
	world->writing = sem_open(FORKSEM, O_CREAT, S_IRWXU, 1);
}

int	init_world(t_world *world, int argc, char **argv)
{
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
	if (!world->philo)
		return (error(MALLOC_ERR, world));
	init_semaphore(world);
	return (init_philo(world));
}

static int	end_of_the_world(t_world *world)
{
	int	status;
	int	i;

	status = 0;
	printf("en attente status : %d\n", status);
	waitpid(0, &status, 0);
	printf("recu : %d\n", status);
	i = 0;
	while (i < world->nb_philo)
		kill(world->philo[i++].pid, SIGINT);
	if (sem_close(world->forks) || sem_close(world->forks))
		return (SEM_ERR);
	sem_unlink(FORKSEM);
	sem_unlink(WRITESEM);
	return (NO_ERR);
}

int	start_world(t_world *world)
{
	int		i;
	int		pid;
	t_philo	*philo;

	philo = world->philo;
	world->t0 = get_timestamp();
	i = 0;
	while (i < world->nb_philo)
	{
		pid = fork();
		if (pid == 0)
			philo_life(&philo[i]);
		if (pid < 0)
			return (FORK_ERR);
		world->philo[i].pid = pid;
		i++;
	}
	return (end_of_the_world(world));
}
