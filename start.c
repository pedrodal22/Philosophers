/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:12:30 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/13 20:29:15 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void even_routine(t_general *general, t_philo *philo)
// {
// 	while (general->phil_dead == 0)
// 	{
// 		go_eat();
// 		if (general->phil_dead != 0)
// 			return ;
// 		go_sleep(general, philo);
// 		if (general->phil_dead != 0)
// 			return ;
// 	}
// }

// void do_it(t_general *general, t_philo *philo)
// {
// 	if (general->nbr_philo == 1)
// 		one_phil();
// 	else if (general->nbr_philo % 2 == 0)
// 		solve_even(general, philo);
// 	else if (general->nbr_philo % 2 == 1)
// 		solve_odd();
// }

	void start_general(t_general *general, char **argv, int argc)
	{
		general->nbr_philo = ft_atoi(argv[1]);
		general->tm_die = ft_atoi(argv[2]);
		general->tm_eat = ft_atoi(argv[3]);
		general->tm_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			general->x_eat = ft_atoi(argv[5]);
		else
			general->x_eat = 0; // Default value if no extra argument
		struct timeval time;
		gettimeofday(&time, NULL);
		general->starting_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
		general->phil_dead = 0;
	}

	void start_philo(t_general *general)
	{
		int i;
		t_philo *philo;
		pthread_t monitor_thread_id;
		philo = malloc(sizeof(t_philo) * general->nbr_philo);
		if(philo == NULL)
			exit(1); //vou ter que alterar esta linha no futuro para dar free das coisas. chamar uma funçao que dá free, para meter um exit(1) no final da mesma.
		general->forks = malloc(sizeof(pthread_mutex_t) * general->nbr_philo);
		if (general->forks == NULL)
			exit(1); //vou ter que alterar esta linha no futuro para dar free das coisas. chamar uma funçao que dá free, para meter um exit(1) no final da mesma.
		i = 0;
		while(i < general->nbr_philo)
		{
			if(pthread_mutex_init(&general->forks[i], NULL) != 0)	
				exit(1); //vou ter que alterar esta linha no futuro para dar free das coisas. chamar uma funçao que dá free, para meter um exit(1) no final da mesma.
			i++;
		}
		i = 0;
		while(i < general->nbr_philo)
		{
			philo[i].phil_index = i;
			philo[i].times_eat = 0;
			philo[i].nbr_meals = 0;
			philo[i].lst_time_eat = time_rn();
			philo[i].r_fork = &general->forks[i];
			philo[i].general = general;
			if(i == 0)
				philo[i].l_fork = &general->forks[general->nbr_philo - 1];
			else
				philo[i].l_fork = &general->forks[i - 1];
			i++;
		}
		if (pthread_create(&monitor_thread_id, NULL, &start_monitor, philo) != 0)
			exit(1); //tenho que mudar isto para um free no futuro para nao haver leaks.
		i = 0;
		while(i < general->nbr_philo)
		{
			if(pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]) != 0)
				dead_phil(general, philo); //vou ter que alterar esta linha no futuro para dar free das coisas. chamar uma funçao que dá free, para meter um exit(1) no final da mesma.
			i++;
		}
		i = 0;
		pthread_join(monitor_thread_id, NULL);
		while(i < general->nbr_philo)
		{
			if(pthread_join(philo[i].thread_id, NULL) != 0)
				dead_phil(general, philo); //vou ter que alterar esta linha no futuro para dar free das coisas. chamar uma funçao que dá free, para meter um exit(1) no final da mesma.
			i++;
		}
	}


/* a função estar philo em principio está pronta. 
cria as mutexes para todos os garfos, e começa as threads. 
preciso da funcao routine para correr quando as threads começarem.
acho que a funcao routine vai ter que começar, por exemplo, uns a comer,
e os outros a dormir. isso vai também depender se forem par ou impar. há que ter
atençao a isso. chamo a funçao start philo em ambos os casos, mas faço um if even ou if odd.
tenho que testar com 3 philos, ou entao faço hardcode. de 3*/