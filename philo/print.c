/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:45:59 by lhopp             #+#    #+#             */
/*   Updated: 2024/08/26 14:46:05 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(const t_philosopher *philo, char *str)
{
	struct timeval	tv;
	struct timezone	tz;
	long			timestamp_in_ms;

	gettimeofday(&tv, &tz);
	timestamp_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("%ld %d %s\n", timestamp_in_ms, philo->id, str);
}
