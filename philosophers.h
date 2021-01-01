#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "utils.h"
#include <limits.h>
int g_ph_count;
time_t g_t_to_die;
time_t g_t_to_eat;
time_t g_t_to_sleep;
int g_num_of_t_to_eat;

typedef struct philo
{
	int *l_fork;
	int *r_fork;
	int life_time;


}			t_philo;

#endif
