/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:47:24 by salahian          #+#    #+#             */
/*   Updated: 2025/05/28 15:46:34 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// t_data  *get_data_struct(void)
// {
//         static  t_data *data;

//         return (data);
// }

void    ft_bzero(void *s, size_t n)
{
        size_t                  i;
        unsigned char   *p;

        i = 0;
        p = (unsigned char *)s;
        while (i < n)
        {
                p[i] = 0;
                i++;
        }
}

int     ft_atoi(const char *str, int *flag)
{
        long    re;
        int             i;

        i = 0;
        re = 0;
        if (str[i] >= '0' && str[i] <= '9')
        {
                while (str[i])
                {
                        if (re > ((LONG_MAX - (str[i] - '0')) / 10))
                        {
                                *flag = 1;
                                break ;
                        }
                        if (str[i] < '0' || str[i] > '9')
                        {
                                *flag = 1;
                                break ;
                        }
                        re = (re * 10) + (str[i] - '0');
                        i++;
                }
        }
        else
                *flag = 1;
        return ((int)re);
}

void    init_philo(t_philo *philo)
{
//     philo->index = 0;
//     philo->t_eat = 0;
//     philo->t_sleep = 0;
//     philo->nbr_of_meal = 0;
    philo->last_meal = get_curr_time();
    pthread_mutex_init(&philo->last_meal_mtx, NULL);
    pthread_mutex_init(philo->right_fork, NULL);
    pthread_mutex_init(&philo->write_mtx, NULL);
    if (philo->left_fork)
        pthread_mutex_init(philo->left_fork, NULL);
}

void    init_forks(pthread_mutex_t *fork, int nbr)
{
        int     i;

        i = 0;
        while (i < nbr)
        {
                pthread_mutex_init(&fork[i], NULL);
                i++;
        }
}