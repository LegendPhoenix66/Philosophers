/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:04:30 by lhopp             #+#    #+#             */
/*   Updated: 2024/08/26 15:04:30 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_eat(const t_philosopher *philosopher)
{
	print_log(philosopher, "is hungry");
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->args->forks[philosopher->id]);
		print_log(philosopher, "is picking up the left fork");
		pthread_mutex_lock(&philosopher->args->forks[(philosopher->id + 1)
			% philosopher->args->num_philosophers]);
		print_log(philosopher, "is picking up the right fork");
	}
	else
	{
		pthread_mutex_lock(&philosopher->args->forks[(philosopher->id + 1)
			% philosopher->args->num_philosophers]);
		print_log(philosopher, "is picking up the right fork");
		pthread_mutex_lock(&philosopher->args->forks[philosopher->id]);
		print_log(philosopher, "is picking up the left fork");
	}
	print_log(philosopher, "is eating");
	usleep(philosopher->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philosopher->args->forks[(philosopher->id + 1)
		% philosopher->args->num_philosophers]);
	print_log(philosopher, "is putting down the right fork");
	pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
	print_log(philosopher, "is putting down the left fork");
}

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	i = 0;
	while (philosopher->args->num_times_each_philosopher_must_eat > i++)
	{
		print_log(philosopher, "is thinking");
		philosopher_eat(philosopher);
		print_log(philosopher, "is sleeping");
		usleep(philosopher->args->time_to_sleep * 1000);
	}
	return (NULL);
}

void	start_philosophers(t_args *args)
{
	pthread_t	threads[args->num_philosophers];
	int			i;

	i = 0;
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
}
