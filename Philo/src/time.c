/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:47:06 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/14 22:54:45 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	_timer(long long int tt)
{
	long long int	time;
	long long int	n_time;

	time = cur_time();
	n_time = cur_time();
	while ((n_time - time) < tt)
	{
		n_time = cur_time();
		usleep(10);
	}
}

long long int	cur_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
