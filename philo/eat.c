/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:49:43 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/27 09:49:47 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	determine_forks(const t_philosopher *philosopher, int *left_fork,
		int *right_fork)
{
	if (philosopher->id % 2 == 0)
	{
		*left_fork = philosopher->id;
		*right_fork = (philosopher->id + 1)
			% philosopher->args->num_philosophers;
	}
	else
	{
		*left_fork = (philosopher->id + 1)
			% philosopher->args->num_philosophers;
		*right_fork = philosopher->id;
	}
}

void	handle_single_philosopher(t_args *args, t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->args->forks[philosopher->id]);
	print_log(args, philosopher, "is picking up the left fork");
	while (!philosopher->args->philosopher_died)
		usleep(1000);
	pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
}

void	pick_up_forks(t_args *args, t_philosopher *philosopher)
{
	int	first_fork;
	int	second_fork;

	if (philosopher->args->num_philosophers == 1)
	{
		handle_single_philosopher(args, philosopher);
		return ;
	}
	determine_forks(philosopher, &first_fork, &second_fork);
	pthread_mutex_lock(&philosopher->args->forks[first_fork]);
	print_log(args, philosopher, "is picking up the left fork");
	pthread_mutex_lock(&philosopher->args->forks[(second_fork)
		% philosopher->args->num_philosophers]);
	print_log(args, philosopher, "is picking up the right fork");
}

void	put_down_forks(t_args *args, t_philosopher *philosopher)
{
	int	first_fork;
	int	second_fork;

	determine_forks(philosopher, &first_fork, &second_fork);
	if (philosopher->args->philosopher_died)
	{
		pthread_mutex_unlock(&philosopher->args->forks[first_fork]);
		pthread_mutex_unlock(&philosopher->args->forks[(second_fork)
			% philosopher->args->num_philosophers]);
		return ;
	}
	pthread_mutex_unlock(&philosopher->args->forks[first_fork]);
	print_log(args, philosopher, "is putting down the right fork");
	pthread_mutex_unlock(&philosopher->args->forks[(second_fork)
		% philosopher->args->num_philosophers]);
	print_log(args, philosopher, "is putting down the left fork");
}

void	philosopher_eat(t_args *args, t_philosopher *philosopher)
{
	print_log(args, philosopher, "is hungry");
	pick_up_forks(args, philosopher);
	if (!philosopher->args->philosopher_died)
	{
		print_log(args, philosopher, "is eating");
		gettimeofday(&philosopher->last_meal_time, NULL);
		usleep(philosopher->args->time_to_eat * 1000);
	}
	put_down_forks(args, philosopher);
}
