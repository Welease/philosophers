#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "utils.h"
#include <limits.h> //TODO putnbr sinxronization selfmade usleep

int g_ph_count;
time_t g_t_to_die;
time_t g_t_to_eat;
time_t g_t_to_sleep;
int g_num_of_t_to_eat;
int g_start_flag;
struct timeval g_tv;
pthread_mutex_t *g_forks_mass;
pthread_mutex_t g_tmp_mutex;
pthread_mutex_t g_lifecheck_mutex;
pthread_mutex_t g_print_mutex;
pthread_t g_death_thread;
typedef struct timeval time_struct;
typedef struct philo
{
	int num_of_philo;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	time_t life_time;
	pthread_t philo_thread;
	int has_eated;
	int eating_counter;
	time_struct eating_time;
}			t_philo;
time_t get_time();
int pars_argv(char **argv, int flag);
void eating(t_philo *philo);
int init_threads(t_philo *philo_mass);
int start(char **argv, int flag);
void *simulation_start(t_philo *philo);
void philo_death(t_philo *philo);
#endif
