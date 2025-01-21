/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:04:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/27 09:48:27 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_philosophers_done(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philosophers)
	{
		pthread_mutex_lock(&args->philosophers[i].philo_lock);
		if (args->philosophers[i].meals_eaten < args->total_meals)
		{
			pthread_mutex_unlock(&args->philosophers[i].philo_lock);
			return (0);
		}
		pthread_mutex_unlock(&args->philosophers[i].philo_lock);
		i++;
	}
	return (1);
}

static int	check_and_handle_philosopher_died(t_args *shared_args)
{
	int	philosopher_died;

	pthread_mutex_lock(&shared_args->global_lock);
	philosopher_died = shared_args->philosopher_died;
	pthread_mutex_unlock(&shared_args->global_lock);
	return (philosopher_died);
}

static void	run_philosopher_cycle(t_philosopher *philosopher,
		t_args *shared_args)
{
	print_log(shared_args, philosopher, "is thinking");
	philosopher_eat(shared_args, philosopher);
	pthread_mutex_lock(&philosopher->philo_lock);
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&philosopher->philo_lock);
	print_log(shared_args, philosopher, "is sleeping");
	usleep(shared_args->time_to_sleep * 1000);
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philosopher;
	t_args			*shared_args;

	philosopher = (t_philosopher *)arg;
	shared_args = philosopher->args;
	while ((shared_args->total_meals > philosopher->meals_eaten
			|| shared_args->total_meals == -1))
	{
		if (check_and_handle_philosopher_died(shared_args))
			break ;
		run_philosopher_cycle(philosopher, shared_args);
	}
	if (all_philosophers_done(shared_args))
	{
		pthread_mutex_lock(&shared_args->global_lock);
		shared_args->all_philosophers_done = 1;
		pthread_mutex_unlock(&shared_args->global_lock);
	}
	return (NULL);
}

void	start_philosophers(t_args *args)
{
	pthread_t	threads[1000];
	pthread_t	death_thread;
	int			i;

	i = 0;
	pthread_create(&death_thread, NULL, check_death, args);
	while (i < args->num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_thread,
			&args->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < args->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
}
