/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:47:10 by azakarya          #+#    #+#             */
/*   Updated: 2022/12/28 23:08:37 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	main(int ac, char **av)
{
	t_philos	*philos;

	if ((ac == 5 || ac == 6) && check_argv(ac, av) == 0)
	{
		philos = get_args(av);
		if (init_philos(philos) == 1)
			return (1);
	}
	else
		return (write(1, "Error\n", 6), 1);
	return (0);
}
