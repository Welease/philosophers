cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(philo_one)

add_executable(philosophers
        philo_one/initing.c
        philo_one/main.c
        philo_one/parsing.c
        philo_one/philosophers.h
        philo_one/utils.c
        philo_one/utils.h philo_one/philo_funcs.c philo_one/utils2.c philo_one/filling_init_data.c)

add_executable(philosophers2
        philo_two/initing.c
        philo_two/main.c
        philo_two/parsing.c
        philo_two/philosophers.h
        philo_two/utils.c
        philo_two/utils.h)

add_executable(philosophers3
        philo_three/initing.c
        philo_three/main.c
        philo_three/parsing.c
        philo_three/philosophers.h
        philo_three/utils.c
        philo_three/utils.h)