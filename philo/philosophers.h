#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philosopher {
	int id;
	int num_philosophers;
}  philosopher_t;

typedef struct s_args {
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_each_philosopher_must_eat;
}  args_t;

// utils.c
int	ft_atoi(char *str);

// philosophers.c
void start_philosophers(int num_philosophers);

#endif //PHILOSOPHERS_PHILOSOPHERS_H
