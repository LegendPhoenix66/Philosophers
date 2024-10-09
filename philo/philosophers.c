/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:04:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/08/29 15:07:30 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void pick_up_forks(t_philosopher *philosopher)
{

	int first_fork;
	int second_fork;

	if (philosopher->args->num_philosophers == 1) {
		// Special case for one philosopher
		pthread_mutex_lock(&philosopher->args->forks[philosopher->id]);
		print_log(philosopher, "is picking up the left fork");
		// sleep until the philosopher dies
		while (!philosopher->args->philosopher_died)
			usleep(1000);
		pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
		return;
	}

	if (philosopher->id % 2 == 0) {
		first_fork = philosopher->id;
		second_fork = (philosopher->id + 1) % philosopher->args->num_philosophers;
	} else {
		first_fork = (philosopher->id + 1) % philosopher->args->num_philosophers;
		second_fork = philosopher->id;
	}

	pthread_mutex_lock(&philosopher->args->forks[first_fork]);
	print_log(philosopher, "is picking up the left fork");
	pthread_mutex_lock(&philosopher->args->forks[(second_fork)
												 % philosopher->args->num_philosophers]);
	print_log(philosopher, "is picking up the right fork");
}

void put_down_forks(t_philosopher *philosopher)
{
	int first_fork;
	int second_fork;

	if (philosopher->id % 2 == 0) {
		first_fork = philosopher->id;
		second_fork = (philosopher->id + 1) % philosopher->args->num_philosophers;
	} else {
		first_fork = (philosopher->id + 1) % philosopher->args->num_philosophers;
		second_fork = philosopher->id;
	}

	if (philosopher->args->philosopher_died) {
		pthread_mutex_unlock(&philosopher->args->forks[first_fork]);
		pthread_mutex_unlock(&philosopher->args->forks[(second_fork)
													 % philosopher->args->num_philosophers]);
		return;
	}

	pthread_mutex_unlock(&philosopher->args->forks[first_fork]);
	print_log(philosopher, "is putting down the right fork");
	pthread_mutex_unlock(&philosopher->args->forks[(second_fork)
												 % philosopher->args->num_philosophers]);
	print_log(philosopher, "is putting down the left fork");
}

void philosopher_eat(t_philosopher *philosopher)
{
	print_log(philosopher, "is hungry");
	pick_up_forks(philosopher);
	if (!philosopher->args->philosopher_died) {
		print_log(philosopher, "is eating");
		gettimeofday(&philosopher->last_meal_time, NULL);
		usleep(philosopher->args->time_to_eat * 1000);
	}
	put_down_forks(philosopher);
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philosopher;
	t_args			*args;
	int				all_done;

	philosopher = (t_philosopher *)arg;
	args = philosopher->args;
	while ((args->num_times_each_philosopher_must_eat > philosopher->meals_eaten || args->num_times_each_philosopher_must_eat == -1)
		&& !args->philosopher_died)
	{
		print_log(philosopher, "is thinking");
		philosopher_eat(philosopher);
		if (args->philosopher_died)
			break;
		philosopher->meals_eaten++;
		print_log(philosopher, "is sleeping");
		usleep(philosopher->args->time_to_sleep * 1000);
	}
	all_done = 1;
	for (int i = 0; i < args->num_philosophers; i++)
	{
		if (args->philosophers[i].meals_eaten < args->num_times_each_philosopher_must_eat)
		{
			all_done = 0;
			break ;
		}
	}
	if (all_done)
	{
		args->all_philosophers_done = 1;
	}
	return (NULL);
}

void	*check_death(void *arg)
{
	t_args			*args;
	int				i;
	struct timeval	current_time;
	long			time_diff;

	args = (t_args *)arg;
	while (!args->all_philosophers_done && !args->philosopher_died)
	{
		i = 0;
		while (i < args->num_philosophers)
		{
			if (args->philosophers[i].meals_eaten >= args->num_times_each_philosopher_must_eat && args->num_times_each_philosopher_must_eat != -1)
			{
				i++;
				continue ;
			}
			gettimeofday(&current_time, NULL);
			time_diff = (current_time.tv_sec * 1000 + current_time.tv_usec
					/ 1000) - (args->philosophers[i].last_meal_time.tv_sec
					* 1000 + args->philosophers[i].last_meal_time.tv_usec
					/ 1000);
			if (time_diff > args->time_to_die+1)
			{
				print_log(&args->philosophers[i], "died");
				args->philosopher_died = 1;
				return (NULL);
			}
			i++;
		}
		usleep(3000);
	}
	return (NULL);
}

void	start_philosophers(t_args *args)
{
	pthread_t	threads[args->num_philosophers];
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
