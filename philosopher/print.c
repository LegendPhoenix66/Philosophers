/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:45:59 by lhopp             #+#    #+#             */
/*   Updated: 2025/01/21 09:35:01 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(t_args *args, const t_philosopher *philo, char *str)
{
	struct timeval	tv;
	struct timezone	tz;
	long			timestamp_in_ms;

	pthread_mutex_lock(&args->global_lock);
	if (args->philosopher_died == 1)
	{
		pthread_mutex_unlock(&args->global_lock);
		return ;
	}
	gettimeofday(&tv, &tz);
	timestamp_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d %s\n", timestamp_in_ms, philo->id, str);
	pthread_mutex_unlock(&args->global_lock);
}
