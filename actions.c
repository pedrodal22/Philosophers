/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:56:03 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/26 14:23:53 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* filósofos pares só comem e dormem.
nos ímpares, somente um deles terá que pensar, pois terá que ficar à espera que os garfos estejam disponíveis. */

/* o problema deve estar no facto de eu nao chamar as outras funções no final das outras. 
eu nao chamo sleep no final de eat, por exemplo. acho que o problema está relacionado com isso. */

void *routine(void *ptr)
{
	t_philo *philo = (t_philo *)ptr;
	t_general *general = philo->general;
	// int times_to_eat;

	// times_to_eat = general->x_eat;
	if(philo->phil_index % 2 == 0)
		go_sleep(general, philo);
	if(general->x_eat > 0)
	{
		while(general->phil_dead == 0)
		{
			go_eat(general, philo);
			go_sleep(general, philo);
		}	
	}
	else
	{
		while(general->phil_dead == 0)
		{
			go_eat(general, philo);
			go_sleep(general, philo);
		}	
	}
	return NULL;
}

void go_eat(t_general *general, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	printf("%lld %d is eating\n", (time_rn() - general->starting_time), philo->phil_index);
	philo->lst_time_eat = time_rn();
	philo->general->x_eat++;
	usleep(general->tm_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->times_eat++;
	long long int elapsed_time = time_rn() - philo->lst_time_eat;
    if (elapsed_time >= general->tm_die)
	{
        general->phil_dead = 1;  // Atualizar o status para morto
		dead_phil(general, philo);
	}
}

void	go_sleep(t_general *general, t_philo *philo)
{
	struct timeval time;
	long long int wakeup_time;
	long long int time_rn;

	gettimeofday(&time, NULL);
	time_rn = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	printf("%lli %i is sleeping\n", (time_rn - (general->starting_time)), philo->phil_index);
	wakeup_time = time_rn + general->tm_sleep;
	while(time_rn < wakeup_time)
	{
		if(wakeup_time - time_rn >= 500)
			usleep(500 * 1000);
		else
			usleep((wakeup_time - time_rn) * 1000);
		gettimeofday(&time, NULL);
		time_rn = ((time.tv_sec * 1000) + (time.tv_usec / 1000));	
	}
}