/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:36:31 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:38:40 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		try_to_take_forks(t_philo *philo)
{
	if (philo->num_of_philo % 2)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, " has taken a left fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, " has taken a right fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, " has taken a right fork\n");
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, " has taken a left fork\n");
	}
	return (0);
}

void	put_forks(t_philo *philo)
{
	if (philo->num_of_philo % 2)
	{
		pthread_mutex_unlock(philo->r_fork);
		usleep(5);
		pthread_mutex_unlock(philo->l_fork);
		usleep(5);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		usleep(5);
		pthread_mutex_unlock(philo->r_fork);
		usleep(5);
	}
}

void	thinking(t_philo *philo)
{
	print_message(philo, " is thinking\n");
}

void	sleeping(t_philo *philo)
{
	print_message(philo, " is sleeping\n");
	my_usleep(philo->input_data->t_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	try_to_take_forks(philo);
	print_message(philo, " is eating\n");
	pthread_mutex_lock(&(philo->life_check_mutex));
	philo->eat_time = get_time() / 1000;
	pthread_mutex_unlock(&(philo->life_check_mutex));
	my_usleep(philo->input_data->t_to_eat * 1000);
	pthread_mutex_lock(&g_tmp_mutex);
	philo->eating_counter++;
	pthread_mutex_unlock(&g_tmp_mutex);
	put_forks(philo);
}
