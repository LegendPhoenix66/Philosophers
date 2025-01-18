/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:06:32 by lhopp             #+#    #+#             */
/*   Updated: 2024/08/26 12:06:33 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_args	args;

	if (init_args(&args, argc, argv))
	{
		return (1);
	}
	start_philosophers(&args);
	cleanup(&args);
	return (0);
}
