/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:26:30 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/12 22:19:14 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_world	world;

	if (argc != 5 && argc != 6)
		return (error(ARG_ERR, &world));
	if (init_world(&world, argc, argv))
		return (error(MALLOC_ERR, &world));
	init_philo(&world);
	return (EXIT_SUCCESS);
}
