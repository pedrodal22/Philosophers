/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:29:53 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/24 19:41:35 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *start_monitor(void *ptr)
{
	t_philo *philos = (t_philo *)ptr;
	t_general *general = philos[0].general;
	int i;
	long long tm_since_lst_meal;

	i = 0;
	tm_since_lst_meal = 0;
	while(general->phil_dead == 0)
	{
		while(i < general->nbr_philo)
		{
			pthread_mutex_lock(&general->forks[i]);
			tm_since_lst_meal = ((time_rn())  - philos[i].lst_time_eat);
			if (tm_since_lst_meal >= general->tm_die)
			{
				general->phil_dead = 1;
				pthread_mutex_unlock(&general->forks[i]);
				printf("philo %i has died\n", i);
				dead_phil(general, philos);
			}
			pthread_mutex_unlock(&general->forks[i]);
			i++;
		}
		i = 0;
		usleep(10);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_general *general = NULL;

	if (check_all(argc, argv) == 1)
		return (print_error(0), 1);
	general = malloc(sizeof(t_general));
	start_general(general, argv, argc);
	start_philo(general);
}

/* nao tenho condição para ver se o número de refeiçoes já feitas corresponde ao número de refeições objetivo para cada phil */