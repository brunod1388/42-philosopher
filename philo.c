/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:43:47 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/04 01:35:58 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(t_rules *rules, int argc, char **argv)
{
	rules->nb_philo = atoi(argv[1]);
	rules->die_time = atoi(argv[2]);
	rules->eat_time = atoi(argv[3]);
	rules->sleep_time = atoi(argv[4]);
	if (argc == 6)
		rules->nb_eat = atoi(argv[5]);
	else
		rules->nb_eat = -1;
}

int	main(int argc, char **argv)
{
	t_philo	p;

	if (argc != 5 && argc != 6)
	{
		printf("Error enter ./philo <nb_philo> <die_time>");
		printf(" <eat_time> <sleep_time> <nb_eat(optional)>\n");
		return (EXIT_SUCCESS);
	}
	philo_init(&p, argc, argv);
	
	
	return (EXIT_SUCCESS);
}
