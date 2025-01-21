/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:45:43 by lhopp             #+#    #+#             */
/*   Updated: 2025/01/21 07:45:47 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosopher_death(t_args *args, int i)
{
	struct timeval	current_time;
	long			time_diff;

	pthread_mutex_lock(&args->philosophers[i].philo_lock);
	if (args->philosophers[i].meals_eaten >= args->total_meals
		&& args->total_meals != -1)
	{
		pthread_mutex_unlock(&args->philosophers[i].philo_lock);
		return (0);
	}
	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (args->philosophers[i].last_meal_time.tv_sec * 1000
			+ args->philosophers[i].last_meal_time.tv_usec / 1000);
	if (time_diff > args->time_to_die + 1)
	{
		print_log(args, &args->philosophers[i], "died");
		pthread_mutex_lock(&args->global_lock);
		args->philosopher_died = 1;
		pthread_mutex_unlock(&args->global_lock);
		pthread_mutex_unlock(&args->philosophers[i].philo_lock);
		return (1);
	}
	pthread_mutex_unlock(&args->philosophers[i].philo_lock);
	return (0);
}

static int	check_all_philosophers(t_args *args)
{
	int	philosopher_index;

	philosopher_index = 0;
	while (philosopher_index < args->num_philosophers)
	{
		if (check_philosopher_death(args, philosopher_index))
			return (1);
		philosopher_index++;
	}
	return (0);
}

void	*check_death(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	while (1)
	{
		pthread_mutex_lock(&args->global_lock);
		if (args->all_philosophers_done || args->philosopher_died)
		{
			pthread_mutex_unlock(&args->global_lock);
			break ;
		}
		pthread_mutex_unlock(&args->global_lock);
		if (check_all_philosophers(args))
			return (NULL);
		usleep(3000);
	}
	return (NULL);
}
