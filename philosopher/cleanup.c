/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:20:21 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/27 09:51:12 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philosophers)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->philosophers[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&args->global_lock);
	free(args->forks);
	free(args->philosophers);
}
