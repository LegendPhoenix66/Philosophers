#include "philosophers.h"

void philosopher_init(philosopher_t *philosopher, int id, int num_philosophers) {
	philosopher->id = id;
	philosopher->num_philosophers = num_philosophers;
}

void *philosopher_thread(void *arg) {
	philosopher_t *philosopher = (philosopher_t *)arg;
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

int ft_atoi(const char *str) {
	int result = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		result = result * 10 + str[i] - '0';
	}
	return result;
}

int main(int argc, char *argv[]) {
	// Check if the number of arguments is correct
	if (argc != 2) {
		printf("Usage: %s <number_of_philosophers>\n", argv[0]);
		return 1;
	}

	// Get the number of philosophers
	int num_philosophers = ft_atoi(argv[1]);

	// Check if the number of philosophers is correct
	if (num_philosophers < 2) {
		printf("The number of philosophers must be at least 2\n");
		return 1;
	}

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

	return 0;
}