#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "utils.h"
#include <limits.h>
int g_ph_count;
time_t g_t_to_die;
time_t g_t_to_eat;
time_t g_t_to_sleep;
int g_num_of_t_to_eat;
pthread_t eating_thread;
pthread_t sleeping_thread;
pthread_t thinking_thread;
int *g_forks_mass; //TODO make mutex's mass
struct timeval g_tv;
pthread_mutex_t eat_mutex;


typedef struct timeval time_struct;
typedef struct philo
{
	int num_of_philo;
	int l_fork;
	int r_fork;
	time_t life_time;
	int eating_flag;
	int sleeping_flag;
	int thinking_flag;
	pthread_t philo_thread;
}			t_philo;

int pars_argv(char **argv, int flag);
void *eating(t_philo *philo);
#endif
