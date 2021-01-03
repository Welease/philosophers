#ifndef PHILOSOPHERS_UTILS_H
#define PHILOSOPHERS_UTILS_H
#include <stdlib.h>
#include <unistd.h>
long long			ft_atoll(char *str);
size_t	ft_strlen(const char *str);
void    ft_putnbr_fd(time_t n, int fd);
void my_usleep(suseconds_t time);
#endif //PHILOSOPHERS_UTILS_H
