/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:57:17 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 23:00:19 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atol(char *str)
{
	unsigned long long	buf;

	buf = 0;
	while (*str)
	{
		buf *= 10;
		buf += *str - '0';
		str++;
	}
	return (buf);
}

unsigned long	ft_strlen(const char *str)
{
	unsigned long	length;

	length = 0;
	while (str[length] != 0)
		length++;
	return (length);
}

char	check_death(t_philos *philo)
{
	unsigned long	c;

	c = 0;
	while (++c <= philo->rules->philo_num)
	{
		if (ft_time(&philo[c - 1], PS_DEAD)
			&& philo->eatcount != philo->rules->musteat)
		{
			pthread_mutex_lock(philo->rules->mutex);
			philo[c - 1].state = PS_DEAD;
			put_msg(&philo[c - 1]);
			philo->rules->death = 1;
			return (1);
		}
	}
	return (0);
}

unsigned long	_timer(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_sec * 1000 + tval.tv_usec / 1000);
}

char	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}
