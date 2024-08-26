/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:07:51 by lhopp             #+#    #+#             */
/*   Updated: 2024/08/26 12:13:30 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_args *args)
{
	int	i;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->num_philosophers);
	i = 0;
	while (i < args->num_philosophers)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philosophers(t_args *args)
{
	int	i;

	args->philosophers = malloc(sizeof(t_philosopher) * args->num_philosophers);
	i = 0;
	while (i < args->num_philosophers)
	{
		args->philosophers[i].id = i;
		args->philosophers[i].args = args;
		i++;
	}
	return (0);
}

int	init_args(t_args *args, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n",
			argv[0]);
		return (1);
	}
	args->num_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->num_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (args->num_times_each_philosopher_must_eat < 0)
		{
			printf("Invalid arguments\n");
			return (1);
		}
	}
	else
		args->num_times_each_philosopher_must_eat = -1;
	if (args->num_philosophers < 2 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	init_forks(args);
	init_philosophers(args);
	return (0);
}
