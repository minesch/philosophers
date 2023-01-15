/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:15:53 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:34:24 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_philo
{
	int				philo_index;
	int				eat_count;
	long long		current_time;
	long long		start_time;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_nbr;
	pthread_t		philo_thread;
	pthread_mutex_t	*mutex_l_fork;
	pthread_mutex_t	monitoring_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*mutex_r_fork;
}	t_philo;

typedef struct s_main
{
	int				philo_nbr;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_nbr;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*print_mutex;
	t_philo			*philo;
}	t_main;

//validation.c
long long int	ft_atoi(const char *str);
void			_timer(unsigned long time);
int				ft_is_digit_s(char *str);
int				ft_valid_args(int argc, char **argv);
long long		cur_time(void);

//check.c
void			ft_print_message(t_philo *philo, char *str);
int				death_check(t_philo *philo);
int				thread_cycle_limit(t_main *rules);
void			ft_monitoring(t_main *rules);

//life.c
int				create_philo(t_main *rules);
void			*routine(void *arg);

//init.c
int				init_philo(t_main *rules);
int				init_mutexes(t_main *rules);
int				get_args( int argc, char **argv, t_main *rules);
#endif
