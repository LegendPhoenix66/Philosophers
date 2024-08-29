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

void	philosopher_eat(t_philosopher *philosopher)
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
	gettimeofday(&philosopher->last_meal_time, NULL);
	usleep(philosopher->args->time_to_eat * 1000);
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_unlock(&philosopher->args->forks[(philosopher->id + 1)
			% philosopher->args->num_philosophers]);
		print_log(philosopher, "is putting down the right fork");
		pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
		print_log(philosopher, "is putting down the left fork");
	}
	else
	{
		pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
		print_log(philosopher, "is putting down the left fork");
		pthread_mutex_unlock(&philosopher->args->forks[(philosopher->id + 1)
			% philosopher->args->num_philosophers]);
		print_log(philosopher, "is putting down the right fork");
	}
}

void	*philosopher_thread(void *arg)
{
    t_philosopher	*philosopher;
    t_args *args;

    philosopher = (t_philosopher *)arg;
    args = philosopher->args;
    while (args->num_times_each_philosopher_must_eat > philosopher->meals_eaten)
    {
        print_log(philosopher, "is thinking");
        philosopher_eat(philosopher);
        philosopher->meals_eaten++;
        print_log(philosopher, "is sleeping");
        usleep(philosopher->args->time_to_sleep * 1000);
    }
    // Check if all philosophers are done
    int all_done = 1;
    for (int i = 0; i < args->num_philosophers; i++)
    {
        if (args->philosophers[i].meals_eaten < args->num_times_each_philosopher_must_eat)
        {
            all_done = 0;
            break;
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
    t_args	*args;
    int		i;
    struct timeval	current_time;
    long	time_diff;

    args = (t_args *)arg;
    while (!args->all_philosophers_done)
    {
        i = 0;
        while (i < args->num_philosophers)
        {
            if (args->num_times_each_philosopher_must_eat != -1 &&
                args->philosophers[i].meals_eaten >= args->num_times_each_philosopher_must_eat)
            {
                i++;
                continue;
            }
            gettimeofday(&current_time, NULL);
            time_diff = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) -
                        (args->philosophers[i].last_meal_time.tv_sec * 1000 + args->philosophers[i].last_meal_time.tv_usec / 1000);
            if (time_diff > args->time_to_die)
            {
                print_log(&args->philosophers[i], "died");
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
	while (i < args->num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_thread,
			&args->philosophers[i]);
		i++;
	}
	pthread_create(&death_thread, NULL, check_death, args);
	i = 0;
	while (i < args->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
}
