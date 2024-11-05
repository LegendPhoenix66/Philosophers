/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:07:51 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/04 15:44:46 by lhopp            ###   ########.fr       */
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
		args->philosophers[i].alive = 1;
		args->philosophers[i].meals_eaten = 0;
		gettimeofday(&args->philosophers[i].last_meal_time, NULL);
		i++;
	}
	return (0);
}

void	print_usage(char *program_name)
{
	printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n",
		program_name);
}

int	validate_args(int num_philosophers, int time_to_die, int time_to_eat,
		int time_to_sleep)
{
	if (num_philosophers < 1 || time_to_die <= 0 || time_to_eat <= 0
		|| time_to_sleep <= 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (1);
}

int	init_t_args(t_args *args, int argc, char *argv[])
{
	args->num_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->all_philosophers_done = 0;
	args->philosopher_died = 0;
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
	if (!validate_args(args->num_philosophers, args->time_to_die,
			args->time_to_eat, args->time_to_sleep))
	{
		return (1);
	}
	return (0);
}

int	init_args(t_args *args, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (init_t_args(args, argc, argv))
		return (1);
	init_forks(args);
	init_philosophers(args);
	return (0);
}
