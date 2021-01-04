#include "philosophers.h"

time_t get_time()
{
	const time_t s_to_ms = 1000000;
	time_t tmp1;
	suseconds_t tmp;
	t_time_sturct tv;
	if (gettimeofday(&tv, NULL) == -1)
		return 0;
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


char *get_message(char *message, t_philo *philo, size_t *len_of)
{
	size_t len;
	size_t len_tmp;
	size_t tmp_len;
	char *tmp;
	char *result;
	int i;
	int j;

	i = 0;
	j = 0;
	len = 6;
	tmp = ft_itoa((philo->num_of_philo) + 1);
	tmp_len = ft_strlen(tmp);
	len += tmp_len;
	len_tmp = ft_strlen(message);
	len += len_tmp;
	result = (char *)malloc(len + 1);
	while (i < 6)
		result[i++] = ' ';
	while (j < (int)tmp_len)
		result[i++] = tmp[j++];
	j = 0;
	while (j < (int)len_tmp)
		result[i++] = message[j++];
	*len_of = len;
	free(tmp);
	return (result);
}

void print_message(t_philo *philo, char *message, int is_dead)
{
	char *tmp;
	size_t len;
	tmp = get_message(message, philo, &len);
	sem_wait(g_print_sem);
	ft_putnbr_fd((get_time()) / 1000, 1);
	write(1, tmp, len);
	if (!is_dead)
		sem_post(g_print_sem);
	free(tmp);
}

