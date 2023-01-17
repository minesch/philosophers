/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:21:53 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 22:39:00 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	check_inputs(int argc, char *argv[])
{
	int	c;

	while (--argc)
	{
		c = 0;
		while (argv[argc][c])
		{
			if (argv[argc][c] < '0' || argv[argc][c] > '9')
				return (0);
			c++;
		}
	}
	return (1);
}

t_main	*get_args(int argc, char *argv[])
{
	t_main	*rules;

	rules = malloc(sizeof(t_main));
	if (!rules)
		return (NULL);
	memset(rules, 0, sizeof(t_main));
	rules->musteat = -1;
	if (argc == 6)
		rules->musteat = ft_atol(argv[--argc]);
	rules->sleep = ft_atol(argv[--argc]);
	rules->eat = ft_atol(argv[--argc]);
	rules->die = ft_atol(argv[--argc]);
	rules->philo_num = ft_atol(argv[--argc]);
	rules->loaded = 0;
	if (rules->philo_num == 0 && ft_free(rules))
		return (NULL);
	rules->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!rules->mutex && ft_free(rules))
		return (NULL);
	return (rules);
}

static void	*ft_calloc(unsigned long size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	memset(ret, 0, size);
	return (ret);
}

t_philos	*create_philos(t_philos *ret, unsigned long count, t_main *rules)
{
	ret = ft_calloc(sizeof(t_philos) * rules->philo_num);
	while (ret != NULL && ++count && count <= rules->philo_num)
	{
		ret[count - 1].num = count;
		ret[count - 1].rules = rules;
		if (count == rules->philo_num && rules->philo_num > 1)
			ret[count - 1].right_fork = ret[0].left_fork;
		else
		{
			ret[count - 1].right_fork = malloc(sizeof(pthread_mutex_t));
			if (!ret[count - 1].right_fork && free_data(ret))
				return (0);
			pthread_mutex_init(ret[count - 1].right_fork, NULL);
		}
		if (count == 1)
		{
			ret[count - 1].left_fork = malloc(sizeof(pthread_mutex_t));
			if (!ret[count - 1].left_fork && free_data(ret))
				return (0);
			pthread_mutex_init(ret[count - 1].left_fork, NULL);
		}
		else
			ret[count - 1].left_fork = ret[count - 2].right_fork;
	}
	return (ret);
}
