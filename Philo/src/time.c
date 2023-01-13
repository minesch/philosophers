/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:47:06 by azakarya          #+#    #+#             */
/*   Updated: 2022/12/27 18:45:28 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	_timer(size_t tt)
{
	size_t	time;
	size_t	n_time;

	time = cur_time();
	n_time = cur_time();
	while ((n_time - time) < tt)
	{
		n_time = cur_time();
		usleep(10);
	}
}

size_t	cur_time(void)
{
	struct timeval	t;
	size_t			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}
