/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:20:21 by lhopp             #+#    #+#             */
/*   Updated: 2024/11/04 15:20:38 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_args *args)
{
	int	i;

	// Destroy each mutex
	for (i = 0; i < args->num_philosophers; i++)
	{
		pthread_mutex_destroy(&args->forks[i]);
	}
	// Free the allocated memory for forks
	free(args->forks);
	// Free the allocated memory for philosophers
	free(args->philosophers);
}
