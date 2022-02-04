/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:25:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 14:32:16 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleapt(t_philo *p, long long time)
{
	long long	tstart;

	tstart = get_timestamp();
	while (p->world->all_alive && !p->world->all_eat
		&& get_timestamp() - tstart < time)
		usleep(UFREQ);
}

static void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->lfork);
	print_state(p, "has taken a fork");
	if (p->rfork != p->lfork)
	{
		pthread_mutex_lock(p->rfork);
		print_state(p, "has taken a fork");
		p->last_meal = get_timestamp();
		print_state(p, "is eating");
		++p->eat_count;
		sleapt(p, p->world->eat_time);
		pthread_mutex_unlock(p->rfork);
	}
	else
		while (p->world->all_alive)
			usleep(UFREQ);
	pthread_mutex_unlock(p->lfork);
}

static int	check_eat(t_world *w)
{
	int	i;

	if (!w->nb_eat)
		return (0);
	i = -1;
	while (++i < w->nb_philo)
		if (w->philo[i].eat_count < w->nb_eat)
			return (0);
	w->all_eat = 1;
	return (1);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	if (p->id % 2)
		usleep(500);
	while (p->world->all_alive && !p->world->all_eat)
	{
		philo_eat(p);
		if (check_eat(p->world))
			break ;
		print_state(p, "is sleeping");
		sleapt(p, p->world->sleep_time);
		print_state(p, "is thinking");
	}
	return (NULL);
}
