/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 14:44:39 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <libc.h>
# include <stdlib.h>
# define MAX_PHILO 50
# define UFREQ	200

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pthread;

enum
{
	NO_ERR,
	ARG_ERR,
	FARGS_ERR,
	MALLOC_ERR,
	MUTEX_ERR,
	TRD_ERR,
	TRD_JOIN_ERR,
	MUTEX_DSTR_ERR
};

typedef struct s_philo	t_philo;

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
	t_mutex		*fork;
	t_mutex		writing;
}	t_world;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long long	last_meal;
	t_pthread	trd;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_world		*world;
}	t_philo;

int			init_world(t_world *world, int argc, char **argv);
int			start_world(t_world *world);

void		*philo_life(void *philo);
void		print_state(t_philo *p, char *s);

long long	get_timestamp(void);
long long	get_utime(void);

int			error(int errno, t_world *world);

#endif
