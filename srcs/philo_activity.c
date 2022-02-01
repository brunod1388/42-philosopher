/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:25:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/12 23:37:59 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_philostate(int time, t_philo *philo)
{
	printf("%dms %d ", time, philo->id);
	if (philo->state == SLEEPING)
		printf("is sleeping\n")
	if (philo->state == EATING)
		printf("is eating\n")
	if (philo->state == thinking)
		printf("is sleeping\n")
	if (philo->state == DEAD)
		printf("died\n")
}

void	philo_think(t_philo *p)
{
	p->state = EATING;
	print_philostate(get_timestamp - p->world->t0, p);
}

void	philo_eat(t_philo *p)
{
	long long	tstart;

	tstart = get_timestamp;

	while (get_timestamp - tstart < p->world->eat_time)

	++p->eat_count;
	p->state = SLEEPING;
	print_philostate(get_timestamp - p->world->t0, p);
}

void	philo_sleep(t_philo *p)
{
	long long	tstart;

	tstart = get_timestamp;
	while (get_timestamp - tstart < p->world->eat_time
			&& get_timestamp - p->world->t0 < p->world->die_time)
		usleep(UFREQ);
	if (get_timestamp - p->world->t0 < p->world->die_time)
		p->state = DEAD;
	else
		p->state = THINKING;
	print_philostate(get_timestamp - p->world->t0, p);
}

int	check_eat(t_world *w)
{
	int	i;

	if (!w->nb_eat)
		return (0);
	i = -1;
	while (++i < w->nb_philo)
		if (w->philo[i].eat_count < w->nb_eat)
			return (0);
	return (1);
}
