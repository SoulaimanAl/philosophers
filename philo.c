/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:02:16 by salahian          #+#    #+#             */
/*   Updated: 2025/05/27 17:49:16 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t diff_time(void)
{
    static time_t first_time = 1;
    static struct timeval start;
    static struct timeval now;
   /// pthread_mutex_t lock;

    //pthread_mutex_init(&lock, NULL);
    //pthread_mutex_lock(&lock);
    if (first_time)
    {
        gettimeofday(&start, NULL);
        first_time = 0;
    }
    gettimeofday(&now, NULL);
    //pthread_mutex_unlock(&lock);
    //pthread_mutex_destroy(&lock);
    return (((now.tv_sec - start.tv_sec) * 1000) + ((now.tv_usec - start.tv_usec) / 1000));
}

time_t get_curr_time(void)
{
    static time_t first_time = 1;
    static struct timeval start;
    static struct timeval now;

    if (first_time)
    {
        gettimeofday(&start, NULL);
        first_time = 0;
    }
    gettimeofday(&now, NULL);
    return (((now.tv_sec) * 1000) + ((now.tv_usec) / 1000));
}

int parse_arg(char *av[], t_data **data, int ac)
{
    int     flag;
    
    if (ac > 6 || ac < 5)
        return (0);
    flag = 0;
    (*data)->nbr_philo = ft_atoi(av[1], &flag);
    (*data)->t_die = (size_t)ft_atoi(av[2], &flag);
    (*data)->t_eat = (size_t)ft_atoi(av[3], &flag);
    (*data)->t_sleep = (size_t)ft_atoi(av[4], &flag);
    if (ac == 6)
        (*data)->nbr_of_meal = ft_atoi(av[5], &flag);
    else
        (*data)->nbr_of_meal = INT_MAX;
    if (flag)
        return (0);
    return (1);
}

int main(int ac, char *av[])
{
    t_data  *data;

    data = ft_malloc(sizeof(t_data), 1);
    ft_bzero(data, sizeof(data));
    // data->nbr_philo = ft_atoi(av[1]);
    // data->t_die = ft_atoi(av[2]);
    // data->t_eat = ft_atoi(av[3]);
    // data->t_sleep = ft_atoi(av[4]);
    //data->nbr_of_meal = ft_atoi(av[5]);
    if (!parse_arg(av, &data, ac))
    {
        printf("Error:/n not valid argument\n");
        return (1);
    }
    create_philo(data);
    return (0);
}