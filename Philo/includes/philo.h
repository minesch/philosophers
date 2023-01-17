/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:58:11 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 23:06:03 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef enum e_philostates
{
	PS_NONE,
	PS_DEAD,
	PS_SLEEPING,
	PS_EATING,
	PS_THINKING,
	PS_FORK
}				t_philostates;

typedef struct s_main
{
	unsigned long		die;
	unsigned long		eat;
	unsigned long		sleep;
	long long			musteat;
	unsigned long		basetime;
	pthread_mutex_t		*mutex;
	unsigned long		philo_num;
	unsigned long		loaded;
	char				death;
}				t_main;

typedef struct s_philos
{
	t_main			*rules;
	t_philostates	state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	actiontime;
	unsigned long	deathtime;
	long long		eatcount;
	unsigned long	num;
}				t_philos;

//life.c
void			ft_wait(t_philos	*philos);
char			free_data(t_philos *ptr);
char			init_philos(unsigned long c, t_philos *philos, t_main *rules);

//check.c
t_main			*get_args(int argc, char *argv[]);
char			check_inputs(int argc, char *argv[]);
t_philos		*create_philos(t_philos *ret, unsigned long count, \
				t_main *rules);

//utils.c
unsigned long	ft_strlen(const char *str);
char			check_death(t_philos *philo);
unsigned long	_timer(void);
unsigned long	ft_atol(char *str);
char			ft_free(void *ptr);

//helper.c
void			eat(t_philos *philo);
void			sleeping(t_philos *philo);
void			thinking(t_philos *philo);
void			put_msg(t_philos *philo);
unsigned long	ft_time(t_philos *philo, t_philostates state);
#endif
