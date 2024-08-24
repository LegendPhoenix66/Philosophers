#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philosopher {
	int id;
	struct s_args *args;
}  philosopher_t;

typedef struct s_args {
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_each_philosopher_must_eat;
	struct s_philosopher *philosophers;
}  args_t;

// utils.c
int	ft_atoi(char *str);

// philosophers.c
void start_philosophers(int num_philosophers);

// init.c
int init_args(args_t *args, int argc, char *argv[]);

#endif //PHILOSOPHERS_PHILOSOPHERS_H
