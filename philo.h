/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/04 01:41:54 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <libc.h>
# include <stdlib.h>
# define MAX_PHILO 150

typedef struct s_philo
{
	int		id;
	int		state;
	int		last_meal_time;
}	t_philo;

typedef struct s_world
{
	int		nb_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		nb_eat;
}	t_world;



#endif
