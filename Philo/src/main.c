/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:57:32 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 22:56:48 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_main		*rules;
	t_philos	*philosophers;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Invalid Argument Amount\n", 32);
		return (1);
	}
	if (!check_inputs(argc, argv))
	{
		write(2, "Error: Invalid Argument Types\n", 31);
		return (1);
	}
	rules = get_args(argc, argv);
	if (!rules)
		return (1);
	philosophers = create_philos(0, 0, rules);
	return (init_philos(0, philosophers, rules));
}
