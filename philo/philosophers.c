#include "philosophers.h"

void philosopher_init(t_philosopher *philosopher, int id, int num_philosophers) {
	philosopher->id = id;
	philosopher->num_philosophers = num_philosophers;
}

void *philosopher_thread(void *arg) {
	pthread_mutex_t forks[philosopher->num_philosophers];

	while (1) {
		printf("Philosopher %d is thinking\n", philosopher->id);

		// Sleep for a random amount of time
		usleep(1000000);

		printf("Philosopher %d is hungry\n", philosopher->id);

		// Try to pick up the left fork
		pthread_mutex_lock(&forks[philosopher->id]);
		printf("Philosopher %d picked up the left fork\n", philosopher->id);

		// Try to pick up the right fork
		pthread_mutex_lock(&forks[(philosopher->id + 1) % philosopher->num_philosophers]);
		printf("Philosopher %d picked up the right fork\n", philosopher->id);

		printf("Philosopher %d is eating\n", philosopher->id);

		// Sleep for a random amount of time
		usleep(1000000);

		// Put down the right fork
		pthread_mutex_unlock(&forks[(philosopher->id + 1) % philosopher->num_philosophers]);
		printf("Philosopher %d put down the right fork\n", philosopher->id);

		// Put down the left fork
		pthread_mutex_unlock(&forks[philosopher->id]);
		printf("Philosopher %d put down the left fork\n", philosopher->id);
	}

	return NULL;
}

void start_philosophers(int num_philosophers) {
	// Initialize the philosophers
	philosopher_t philosophers[num_philosophers];
	for (int i = 0; i < num_philosophers; i++) {
		philosopher_init(&philosophers[i], i, num_philosophers);
	}

	// Create the threads
	pthread_t threads[num_philosophers];
	for (int i = 0; i < num_philosophers; i++) {
		pthread_create(&threads[i], NULL, philosopher_thread, &philosophers[i]);
	}

	// Wait for the threads to finish
	for (int i = 0; i < num_philosophers; i++) {
		pthread_join(threads[i], NULL);
	}
}