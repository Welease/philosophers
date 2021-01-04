/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:34:11 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:47:58 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t		get_time(void)
{
	const time_t	s_to_ms = 1000000;
	time_t			tmp1;
	suseconds_t		tmp;
	t_time_sturct	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	tmp1 = tv.tv_sec - g_tv.tv_sec;
	tmp = tv.tv_usec - g_tv.tv_usec;
	if (tmp < 0)
	{
		tmp1--;
		tmp += s_to_ms;
	}
	if (tmp1 > 0)
		tmp += tmp1 * s_to_ms;
	return (tmp);
}

void		print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&g_print_mutex);
	ft_putnbr_fd((get_time()) / 1000, 1);
	write(1, "    ", 6);
	ft_putnbr_fd((time_t)(philo->num_of_philo) + 1, 1);
	write(1, message, ft_strlen(message));
	if (ft_strncmp(message, " is dead\n", 9))
		pthread_mutex_unlock(&g_print_mutex);
}

void		my_usleep(suseconds_t time)
{
	t_time_sturct tmp1;
	t_time_sturct tmp2;

	gettimeofday(&tmp1, NULL);
	gettimeofday(&tmp2, NULL);
	while (tmp2.tv_sec * 1000000 + tmp2.tv_usec - tmp1.tv_sec * 1000000 -
					tmp1.tv_usec <= time)
	{
		usleep(10);
		gettimeofday(&tmp2, NULL);
	}
}

void		philo_death(t_philo *philo)
{
	print_message(philo, " is dead\n");
}
