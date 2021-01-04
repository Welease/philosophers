#ifndef PHILOSOPHERS_PHILOSOPHERS_H
#define PHILOSOPHERS_PHILOSOPHERS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "utils.h"
#include <semaphore.h>
#include <limits.h> //TODO putnbr sinxronization selfmade usleep
#include <sys/types.h>
#include <signal.h>

sem_t  *g_forks_sem;
sem_t *g_print_sem;
sem_t *g_waiter;
sem_t *g_lifecheck_mutex;
sem_t *g_print_mutex;
sem_t *g_tmp_mutex;
int g_status;
struct timeval g_tv;


typedef struct timeval time_struct;

typedef struct input {
	int ph_count;
	time_t t_to_die;
	time_t t_to_eat;
	time_t t_to_sleep;
	int num_of_t_to_eat;
}				t_input_data;

typedef struct philo
{
	int num_of_philo;
	pthread_t philo_thread;
	sem_t *life_check_sem;
	int eating_counter;
	time_t eat_time;
	pid_t ret;
	t_input_data *input_data;
	pthread_t death_thread;
	sem_t *eat_sem_count;
}			t_philo;

time_t get_time();
int pars_argv(char **argv, int flag, t_input_data *input);
void eating(t_philo *philo);
int init_threads(t_philo *philo_mass, t_input_data *input_data, pthread_t g_death_thread);
int start(char **argv, int flag, t_input_data *input_data);
void *simulation_start(t_philo *philo);
void philo_death(t_philo *philo);
void *check_deading(t_philo *mass);
#endif
