/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:16:00 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:48:41 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

int	main(int argc, char **argv)
{
	t_main	*rules;

	rules = malloc(sizeof(t_main));
	if (rules || argc < 5 || argc > 6 || (ft_valid_args(argc, argv) == 0))
	{
		get_args(argc, argv, rules);
		init_mutexes(rules);
		rules->philo = malloc(sizeof(t_philo) * rules->philo_nbr);
		init_philo(rules);
		create_philo(rules);
		return (0);
	}
	free(rules);
	printf("Error\n");
	return (-1);
}
