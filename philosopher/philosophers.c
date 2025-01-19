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
		if (args->philosophers[i].meals_eaten < args->num_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&args->philosophers[i].philo_lock);
			return (0);
		}
		pthread_mutex_unlock(&args->philosophers[i].philo_lock);
		i++;
	}
	return (1);
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philosopher;
	t_args			*args;

	philosopher = (t_philosopher *)arg;
	args = philosopher->args;
	while ((args->num_times_each_philosopher_must_eat > philosopher->meals_eaten
			|| args->num_times_each_philosopher_must_eat == -1))
	{
		pthread_mutex_lock(&args->global_lock);
		if (args->philosopher_died)
		{
			pthread_mutex_unlock(&args->global_lock);
			break ;
		}
		pthread_mutex_unlock(&args->global_lock);
		print_log(args, philosopher, "is thinking");
		philosopher_eat(args, philosopher);
		pthread_mutex_lock(&philosopher->philo_lock);
		philosopher->meals_eaten++;
		pthread_mutex_unlock(&philosopher->philo_lock);
		print_log(args, philosopher, "is sleeping");
		usleep(philosopher->args->time_to_sleep * 1000);
	}
	if (all_philosophers_done(args))
		args->all_philosophers_done = 1;
	return (NULL);
}

int	check_philosopher_death(t_args *args, int i)
{
	struct timeval	current_time;
	long			time_diff;

	pthread_mutex_lock(&args->philosophers[i].philo_lock);
	if (args->philosophers[i].meals_eaten >= args->num_times_each_philosopher_must_eat
		&& args->num_times_each_philosopher_must_eat != -1)
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

void	*check_death(void *arg)
{
	t_args	*args;
	int		i;

	args = (t_args *)arg;
	pthread_mutex_lock(&args->global_lock);
	while (!args->all_philosophers_done && !args->philosopher_died)
	{
		pthread_mutex_unlock(&args->global_lock);
		i = 0;
		while (i < args->num_philosophers)
		{
			if (check_philosopher_death(args, i))
				return (NULL);
			i++;
		}
		usleep(3000);
		pthread_mutex_lock(&args->global_lock);
	}
	pthread_mutex_unlock(&args->global_lock);
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
