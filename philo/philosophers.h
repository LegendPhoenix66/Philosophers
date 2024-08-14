#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_philosopher {
	int id;
	int num_philosophers;
}  philosopher_t;

#endif //PHILOSOPHERS_PHILOSOPHERS_H
