/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:51:23 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/13 23:37:20 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	mop;

	mop = 1;
	res = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if ((str[0] == '-') || (str[0] == '+'))
	{
		if (*str == '-')
			mop *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + ((int)*str - '0');
		str++;
	}
	return (res * mop);
}

t_philos	*get_args(char **av)
{
	t_philos	*philos;
	t_main		*rules;
	int			i;
	i = -1;
	rules = malloc(sizeof(t_main));
	philos = malloc(sizeof(t_philos) * ft_atoi(av[1]));
	rules->start_time = cur_time();
	rules->ph_count = ft_atoi(av[1]);
	rules->die = ft_atoi(av[2]);
	rules->eat = ft_atoi(av[3]);
	rules->sleep = ft_atoi(av[4]);
	rules->print_mutex = malloc(sizeof(pthread_mutex_t *));
	if (av[5])
		rules->max_eat = ft_atoi(av[5]);
	else
		rules->max_eat = -1;
	while (++i < ft_atoi(av[1]))
	{
		philos[i].rules = rules;
		philos[i].index = i;
	}
	return (philos);
}

int	check_argv(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 && av[i][j] > 56)
				return (1);
			j++;
		}
	}
	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) <= 0 && (ft_atoi(av[i]) >= INT_MAX))
			return (1);
	}
	return (0);
}
