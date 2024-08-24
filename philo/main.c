#include "philosophers.h"

int main(int argc, char *argv[]) {
	// Initialize the arguments
	args_t args;
	if (init_args(&args, argc, argv)) {
		return 1;
	}

	// Start the philosophers
	start_philosophers(args.num_philosophers);

	return 0;
}
