#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philosopher {
	int id;
	struct s_args *args;
}  t_philosopher;

typedef struct s_args {
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_each_philosopher_must_eat;
	t_philosopher *philosophers;
	pthread_mutex_t *forks;
}  t_args;

// utils.c
int	ft_atoi(char *str);

// philosophers.c
void start_philosophers(t_args* args);

// init.c
int init_args(t_args *args, int argc, char *argv[]);

// print.c
void print_log(const t_philosopher *philo, char *str);

#endif //PHILOSOPHERS_PHILOSOPHERS_H
