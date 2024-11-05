/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:40:39 by lhopp             #+#    #+#             */
/*   Updated: 2024/10/09 15:41:04 by lhopp            ###   ########.fr       */
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
	struct s_args	*args;
}					t_philosopher;

typedef struct s_args
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_each_philosopher_must_eat;
	int				all_philosophers_done;
	int				philosopher_died;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
}					t_args;

// utils.c
int					ft_atoi(char *str);

// philosophers.c
void				start_philosophers(t_args *args);

// init.c
int					init_args(t_args *args, int argc, char *argv[]);

// print.c
void				print_log(t_args *args, const t_philosopher *philo,
						char *str);

// cleanup.c
void				cleanup(t_args *args);

#endif // PHILOSOPHERS_H
