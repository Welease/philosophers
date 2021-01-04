#ifndef PHILOSOPHERS_UTILS_H
#define PHILOSOPHERS_UTILS_H
#include <stdlib.h>
#include <unistd.h>
long long			ft_atoll(char *str);
size_t	ft_strlen(const char *str);
void    ft_putnbr_fd(time_t n, int fd);
void my_usleep(suseconds_t time);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_itoa(int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
#endif //PHILOSOPHERS_UTILS_H
