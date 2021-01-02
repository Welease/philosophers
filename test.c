#include <stdio.h>
#include "utils.h"

int main()
{
	/*for (time_t i = 10000000000000000000; i < 10000000000000000009; i++)
	{
		ft_putnbr_fd(i, 1);
		write(1, "\n", 1);
	}*/
	write(1, "gds\n", 4);
	suseconds_t t = 10000000;
	my_usleep(t);
	write(1, "sdf\n", 4);
}