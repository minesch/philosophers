/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:47:10 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/13 23:36:40 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	main(int ac, char **av)
{
	t_philos	*philos;

	if ((ac == 5 || ac == 6) && check_argv(ac, av) == 0)
	{
		philos = get_args(av);
		init_philos(philos);
	}
	else
		return (write(1, "Error\n", 6), 1);
	return (0);
}
