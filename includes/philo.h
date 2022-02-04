/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 03:32:11 by bgoncalv         ###   ########.fr       */
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
# define UFREQ	50

typedef pthread_mutex_t	t_mutex;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

enum
{
	NO_ERR = 0,
	ARG_ERR = 1,
	MALLOC_ERR = 2,
	MUTEX_ERR = 3
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
	pthread_t	trd;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_world		*world;
}	t_philo;

int			init_world(t_world *world, int argc, char **argv);
void		start_world(t_world *world);
void		clear_world(t_world *world);

void		*philo_life(void *philo);
void		print_state(t_philo *p, char *s);

long long	get_timestamp(void);
long long	get_utime(void);

int			error(int errno, t_world *world);
void		memdel(void **pt);

#endif
