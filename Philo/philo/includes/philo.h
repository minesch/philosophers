/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:47:04 by azakarya          #+#    #+#             */
/*   Updated: 2022/12/28 23:41:04 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_main
{
	long long int	eat;
	long long int	sleep;
	long long int	die;
	long long int	ph_count;
	long long int	max_eat;
	long long int	start_time;
	pthread_mutex_t	*print;
}	t_main;

typedef struct s_philos
{
	int				index;
	long long int	eat_count;
	long long int	last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_main			*rules;
}	t_philos;

//validation.c
int			ft_atoi(const char *str);
t_philos	*get_args(char **av);
int			check_argv(int ac, char **av);

//init.c
void		*routine(void *value);
int			init_philos(t_philos *philos);
int			create_philos(t_philos *philos);
void		processing(t_philos *philos);

//time.c
void		_timer(size_t tt);
size_t		cur_time(void);

#endif
