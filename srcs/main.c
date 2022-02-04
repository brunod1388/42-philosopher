/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:26:30 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/02/04 14:39:33 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_world	world;
	int		errno;

	if (argc != 5 && argc != 6)
		return (error(ARG_ERR, &world));
	errno = init_world(&world, argc, argv);
	if (errno)
		return (error(errno, &world));
	start_world(&world);
	return (EXIT_SUCCESS);
}
