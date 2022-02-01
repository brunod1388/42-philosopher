/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/12 23:39:02 by bgoncalv         ###   ########.fr       */
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
	MALLOC_ERR = 2
};

typedef struct s_philo	t_philo;

typedef struct s_world
{
	int		nb_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		nb_eat;
	int		t0;
	t_philo	*philo;
	t_mutex	*fork;
	t_mutex	*writing;
}	t_world;

typedef struct s_philo
{
	int			id;
	t_state		state;
	int			last_meal_time;
	int			eat_count;
	pthread_t	trd;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_world		*world;
}	t_philo;

int			init_world(t_world *world, int argc, char **argv);
void		init_philo(t_world *world);
void		clear_world(t_world *world);

void		philo_think(t_philo *p);
void		philo_eat(t_philo *p);
void		philo_sleep(t_philo *p);
int			check_eat(t_world *w);

long long	get_timestamp(void);
long long	get_utime(void);

int			error(int errno, t_world *world);
void		memdel(void **pt);

#endif
