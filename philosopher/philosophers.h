/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:40:39 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/27 09:52:20 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	int				alive;
	struct timeval	last_meal_time;
	pthread_mutex_t	philo_lock;
	struct s_args	*args;
}					t_philosopher;

typedef struct s_args
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
	int				all_philosophers_done;
	int				philosopher_died;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	global_lock;
}					t_args;

// utils.c
int					ft_atoi(char *str);
void				print_usage(char *program_name);

// philosophers.c
void				start_philosophers(t_args *args);

// eat.c
void				philosopher_eat(t_args *args, t_philosopher *philosopher);

// init.c
int					init_args(t_args *args, int argc, char *argv[]);

// print.c
void				print_log(t_args *args, const t_philosopher *philo,
						char *str);

// cleanup.c
void				cleanup(t_args *args);

// death.c
void				*check_death(void *arg);

#endif // PHILOSOPHERS_H
