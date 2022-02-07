/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/06 01:57:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <pthread.h>
# include <semaphore.h>
# include <libc.h>
# include <stdlib.h>
# define MAX_PHILO 50
# define UFREQ	100
# define FORKSEM "/philo_forks"
# define WRITESEM "/philo_write"

enum
{
	NO_ERR,
	ARG_ERR,
	FARGS_ERR,
	MALLOC_ERR,
	FORK_ERR,
	SEM_ERR
};

typedef struct s_philo	t_philo;
typedef unsigned int	t_uint;

typedef struct s_world
{
	int			nb_philo;
	int			nb_eat;
	int			all_alive;
	int			all_eat;
	long long	die_time;
	long long	eat_time;
	long long	sleep_time;
	long long	t0;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*writing;
}	t_world;

typedef struct s_philo
{
	int			id;
	int			pid;
	int			eat_count;
	long long	last_meal;
	t_world		*world;
	pthread_t	the_death;
}	t_philo;

int			init_world(t_world *world, int argc, char **argv);
int			start_world(t_world *world);

void		*philo_life(void *philo);
void		print_state(t_philo *p, char *s);

long long	get_timestamp(void);

int			error(int errno, t_world *world);

#endif
