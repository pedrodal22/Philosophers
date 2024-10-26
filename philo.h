/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:30:01 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/12 21:48:38 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

#include "Libft/libft.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_general
{
	int	nbr_philo;
	int	tm_die;
	int tm_eat;
	int	tm_sleep;
	int	x_eat;
	long long int starting_time;
	int	phil_dead;
	pthread_mutex_t *forks;
}	t_general;

typedef struct s_philo
{
	int phil_index;
	int	times_eat;
	long int lst_time_eat;
	int nbr_meals;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	pthread_t thread_id;
	t_general *general;
}	t_philo;

int				main(int argc, char **argv);
int				check_all(int argc, char **argv);
int				check_arguments(int argc, char **argv);
int 			check_inputs(char **argv);
void			print_error(int error);
int				ft_atoi(const char *str);
void 			start_general(t_general *general, char **argv, int argc);
void 			start_philo(t_general *general);
void			go_sleep(t_general *general, t_philo *philo);
void 			go_eat(t_general *general, t_philo *philo);
long long int 	time_rn(void);
void 			*routine(void *ptr);
int				ft_usleep(size_t ms);
void 			dead_phil(t_general *general, t_philo *philo);
void 			*start_monitor(void *ptr);

#endif