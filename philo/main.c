#include "philosophers.h"

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

	// Start the philosophers
	start_philosophers(num_philosophers);

	return 0;
}
