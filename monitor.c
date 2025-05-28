/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:04:22 by salahian          #+#    #+#             */
/*   Updated: 2025/05/28 18:02:13 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_is_dead(t_philo *philo, int nbr)
{
    static int is_dead;
    int result;
    (void)philo;
    //pthread_mutex_t *lock = get_lock();

    pthread_mutex_lock(philo->is_dead);
    result = 0;
    if (nbr)
        is_dead = 1;
    result = is_dead;
    pthread_mutex_unlock(philo->is_dead);
    return result;
}


int     check_single_philo(t_data *data, int i)
{
    time_t    curr;
    time_t    last_meal;

    pthread_mutex_lock(&data->philo[i]->last_meal_mtx);
    last_meal = data->philo[i]->last_meal;
    pthread_mutex_unlock(&data->philo[i]->last_meal_mtx);
    curr = get_curr_time();
	if ((curr - last_meal) > (time_t)data->t_die)
	{
        check_is_dead(data->philo[i], 1);
		print(data->philo[i], diff_time(), 4);
		return (1);
	}
	return (0);
}

void    *check_philos(void *arg)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    i = 0;
    while (1)
    {
        if (check_single_philo(data, i))
            break ;
        if (i == data->nbr_philo - 1)
            i = 0;
        else
            i++;
        usleep(200);
    }
    return (NULL);
}

