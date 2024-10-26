/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:52:49 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/13 20:28:32 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int time_rn(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	long long int time_rn = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return(time_rn);
}

int	ft_usleep(size_t ms)
{
	size_t	start = time_rn();

	while (ms > (time_rn() - start))
		usleep(500);
	return (0);
}

void dead_phil(t_general *general, t_philo *philo)
{
    int i;

	i = 0;
	while (i < general->nbr_philo)
    {
        pthread_mutex_destroy(&general->forks[i]);
		i++;
    }
	free(general->forks);
	free(philo);
	free(general);
	exit(1);
}

/* parte dos erros do valgrind é por blocos, e o número de blocos é 
igual ao número de filósovos. tenho que dar free a algo relacionado 
com o número de filósofos */

//free(&general->forks[i]);    ---> esta não é a solução