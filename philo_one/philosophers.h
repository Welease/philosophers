/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:40:07 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:46:20 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILOSOPHERS_H
# define PHILOSOPHERS_PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

int				g_start_flag;
struct timeval	g_tv;
pthread_mutex_t	*g_forks_mass;
pthread_mutex_t	g_lifecheck_mutex;
pthread_mutex_t	g_print_mutex;
pthread_mutex_t	g_tmp_mutex;

typedef struct timeval	t_time_sturct;

typedef struct			s_input{
	int		ph_count;
	time_t	t_to_die;
	time_t	t_to_eat;
	time_t	t_to_sleep;
	int		num_of_t_to_eat;
}						t_input_data;

typedef struct			s_philo{
	int				num_of_philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		philo_thread;
	pthread_mutex_t	life_check_mutex;
	time_t			eat_time;
	int				eating_counter;
	t_input_data	*input_data;
}						t_philo;

long long				ft_atoll(char *str);
size_t					ft_strlen(const char *str);
void					ft_putnbr_fd(time_t n, int fd);
void					my_usleep(suseconds_t time);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
time_t					get_time();
int						pars_argv(char **argv, int flag, t_input_data *input);
void					eating(t_philo *philo);
void					philo_death(t_philo *philo);
void					print_message(t_philo *philo, char *message);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					philo_death(t_philo *philo);
int						init_threads(t_philo *philo_mass,
						t_input_data *input_data, pthread_t g_death_thread);
int						start(char **argv, int flag, t_input_data *input_data);
void					*simulation_start(t_philo *philo);
void					forks_mass_init(t_input_data *input_data);
void					fill_mass_of_philo(t_philo *philo_mass,
							t_input_data *input_data);
#endif
