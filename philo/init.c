#include "philosophers.h"

int init_args(args_t *args, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n", argv[0]);
		return (1);
	}
	args->num_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		args->num_times_each_philosopher_must_eat = -1;
	if (args->num_philosophers < 2 || args->time_to_die <= 0 || args->time_to_eat <= 0 || args->time_to_sleep <= 0 || (argc == 6 && args->num_times_each_philosopher_must_eat < 1))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	args->philosophers = malloc(sizeof(philosopher_t) * args->num_philosophers);
	for (int i = 0; i < args->num_philosophers; i++)
	{
		args->philosophers[i].id = i;
		args->philosophers[i].args = args;
	}
	return (0);
}
