/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_init_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welease <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:32:44 by welease           #+#    #+#             */
/*   Updated: 2021/01/04 22:33:29 by welease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			forks_mass_init(t_input_data *input_data)
{
	int		i;

	i = 0;
	while (i < input_data->ph_count)
		pthread_mutex_init(&g_forks_mass[i++], NULL);
}

t_input_data	*get_copy_of_data(t_input_data *input_data)
{
	t_input_data *tmp;

	tmp = (t_input_data *)malloc(sizeof(t_input_data));
	tmp->t_to_eat = input_data->t_to_eat;
	tmp->t_to_die = input_data->t_to_die;
	tmp->num_of_t_to_eat = input_data->num_of_t_to_eat;
	tmp->ph_count = input_data->ph_count;
	tmp->t_to_sleep = input_data->t_to_sleep;
	return (tmp);
}

void			fill_mass_of_philo(t_philo *philo_mass,
									t_input_data *input_data)
{
	int		fork_index;
	int		i;

	i = 0;
	while (i < input_data->ph_count)
	{
		if ((fork_index = i - 1) < 0)
			fork_index = input_data->ph_count - 1;
		philo_mass[i].num_of_philo = i;
		philo_mass[i].l_fork = &g_forks_mass[fork_index];
		philo_mass[i].r_fork = &g_forks_mass[i];
		pthread_mutex_init(&(philo_mass[i].life_check_mutex), NULL);
		philo_mass[i].eating_counter = 0;
		philo_mass[i].input_data = get_copy_of_data(input_data);
		i++;
	}
}
