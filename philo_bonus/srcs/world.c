/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 04:38:25 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/08 04:43:13 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_sem(t_world *world)
{
	sem_close(world->forks);
	sem_close(world->writing);
	sem_close(world->full_eat);
	sem_close(world->death);
	sem_unlink(FORKSEM);
	sem_unlink(WRITESEM);
	sem_unlink(EATSEM);
	sem_unlink(DEATHSEM);
}

static int	end_of_the_world(t_world *world)
{
	int			i;
	pthread_t	eat_thread;
	pthread_t	death_thread;

	pthread_create(&eat_thread, NULL, check_eat, world);
	pthread_create(&death_thread, NULL, check_death, world);
	while (!world->all_eat && world->all_alive)
		usleep(UFREQ);
	while (!world->all_eat)
	{
		sem_post(world->full_eat);
		usleep(UFREQ);
	}
	if (world->all_alive)
		sem_post(world->death);
	i = 0;
	while (i < world->nb_philo)
		kill(world->philo[i++].pid, SIGKILL);
	clean_sem(world);
	free(world->philo);
	return (NO_ERR);
}

int	start_world(t_world *world)
{
	int		i;
	pid_t	pid;

	world->t0 = get_timestamp();
	i = 0;
	while (i < world->nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_life(&world->philo[i]);
		}
		if (pid < 0)
			return (FORK_ERR);
		world->philo[i].pid = pid;
		i++;
	}
	usleep(UFREQ);
	return (end_of_the_world(world));
}
