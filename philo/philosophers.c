#include "philosophers.h"

void *philosopher_thread(void *arg) {
	t_philosopher *philosopher = (t_philosopher *)arg;

	while (1) {
		printf("Philosopher %d is thinking\n", philosopher->id);

		// Sleep for a random amount of time
		usleep(1000000);

		printf("Philosopher %d is hungry\n", philosopher->id);

		// Try to pick up the left fork
		pthread_mutex_lock(&philosopher->args->forks[philosopher->id]);
		printf("Philosopher %d picked up the left fork\n", philosopher->id);

		// Try to pick up the right fork
		pthread_mutex_lock(&philosopher->args->forks[(philosopher->id + 1) % philosopher->args->num_philosophers]);
		printf("Philosopher %d picked up the right fork\n", philosopher->id);

		printf("Philosopher %d is eating\n", philosopher->id);

		// Sleep for a random amount of time
		usleep(1000000);

		// Put down the right fork
		pthread_mutex_unlock(&philosopher->args->forks[(philosopher->id + 1) % philosopher->args->num_philosophers]);
		printf("Philosopher %d put down the right fork\n", philosopher->id);

		// Put down the left fork
		pthread_mutex_unlock(&philosopher->args->forks[philosopher->id]);
		printf("Philosopher %d put down the left fork\n", philosopher->id);
	}

	return NULL;
}

void start_philosophers(t_args * args) {
	// Create the threads
	pthread_t threads[args->num_philosophers];
	for (int i = 0; i < args->num_philosophers; i++) {
		pthread_create(&threads[i], NULL, philosopher_thread, &args->philosophers[i]);
	}

	// Wait for the threads to finish
	for (int i = 0; i < args->num_philosophers; i++) {
		pthread_join(threads[i], NULL);
	}
}