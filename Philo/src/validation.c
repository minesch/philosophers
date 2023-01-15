/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:16:21 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:38:29 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long long int	ft_atoi(const char *str)
{
	int				sign;
	int				i;
	long long int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

void	_timer(unsigned long time)
{
	unsigned long	start_time;

	start_time = cur_time();
	while (cur_time() - start_time < time)
		usleep(100);
}

int	ft_is_digit_s(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int	ft_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_digit_s(argv[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

long long	cur_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
