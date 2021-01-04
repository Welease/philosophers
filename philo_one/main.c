/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:47:31 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:11:19 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*simulation_start(t_philo *philo)
{
	while (!g_start_flag)
		NULL;
	philo->eat_time = get_time() / 1000;
	pthread_detach(philo->philo_thread);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_input_data input_data;

	pthread_mutex_init(&g_print_mutex, NULL);
	pthread_mutex_init(&g_tmp_mutex, NULL);
	pthread_mutex_init(&g_lifecheck_mutex, NULL);
	if (gettimeofday(&g_tv, NULL) == -1)
	{
		write(1, "some problem with gettimeofday func\n", 37);
		return (0);
	}
	if (argc > 6 || argc < 5)
	{
		write(1, "Wrong count of arguments\n", 26);
		return (0);
	}
	else if ((argc == 5 && start(argv, 0, &input_data) == -1)
				|| (argc == 6 && start(argv, 1, &input_data) == -1))
	{
		write(1, "Invalid paramaters\n", 20);
		return (0);
	}
}
