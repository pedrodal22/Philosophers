/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranco- <pfranco-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:37:58 by pfranco-          #+#    #+#             */
/*   Updated: 2024/09/07 16:57:30 by pfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_all(int argc, char **argv)
{
	if(check_arguments(argc, argv) != 0 || check_inputs(argv))
		return (1);
	return (0);
}

int check_arguments(int argc, char **argv)
{
	int i;
	int ii;

	i = 1;
	ii = 0;
	while(i < argc)
	{
		if (argv[i][0] == '0' && argv[i][1] == '\0')
			return (1);
		while (argv[i][ii] != '\0')
		{
			if (argv[i][ii] <= 57 && argv[i][ii] >= 48)
				ii++;
			else
				return (1);
		}
		ii = 0;
		i++;
	}
	return (0);
}

int check_inputs(char **argv)
{
	if (ft_atoi(argv[1]) <= 1 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (1);
	return (0);
}

void print_error(int error)
{
	if (error == 0)
		printf("There is a problem with the arguments.\n");
}