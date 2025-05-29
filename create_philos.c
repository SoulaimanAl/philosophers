/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:13:11 by salahian          #+#    #+#             */
/*   Updated: 2025/05/29 17:09:57 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    create_monitor(t_data *data)
{
    pthread_create(&data->monitor, NULL, check_philos, data);
    pthread_join(data->monitor, NULL);
}

void    join_every_thread(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nbr_philo)
    {
        pthread_join(data->philo[i]->philo, NULL);
        i++;
    }
}

void    get_the_forks(t_philo **philo, t_data *data)
{
    if ((*philo)->index == data->nbr_philo)
    {
        if (((*philo)->index) % 2 != 0)
        {
            (*philo)->right_fork = &(data->fork[0]);
            (*philo)->left_fork = &(data->fork[(*philo)->index - 1]);
        }
        else
        {
            (*philo)->right_fork = &(data->fork[(*philo)->index - 1]);
            (*philo)->left_fork = &(data->fork[0]);
        }
    }
    else if (((*philo)->index) % 2 != 0)
    {
        (*philo)->right_fork = &(data->fork[(*philo)->index]);
        (*philo)->left_fork = &(data->fork[(*philo)->index - 1]);
    }
    else
    {
        (*philo)->right_fork = &(data->fork[(*philo)->index - 1]);
        (*philo)->left_fork = &(data->fork[(*philo)->index]);
    }
}

void    start_philo(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nbr_philo)
    {
        pthread_create(&data->philo[i]->philo, NULL, start_routine, (void *)data->philo[i]);
        i++;
    }
   
}

void clear_all(t_data *data)
{
    int i = 0;

    while (i < data->nbr_philo)
    {
        pthread_mutex_destroy(&data->philo[i]->last_meal_mtx);
        i++;
    }

    // Destroy the shared mutexes only once
    pthread_mutex_destroy(data->dead_mtx);
    pthread_mutex_destroy(&data->write_mtx);

    ft_lstclear(garbage_list());
}


void    fill_philo(t_data **data, int i)
{
    (*data)->philo[i] = ft_malloc(sizeof(t_philo), 1);
    (*data)->philo[i]->index = i + 1;
    (*data)->philo[i]->t_eat = (*data)->t_eat;
    (*data)->philo[i]->t_sleep = (*data)->t_sleep;
    (*data)->philo[i]->nbr_of_meal = (*data)->nbr_of_meal;
    (*data)->philo[i]->t_die = (*data)->t_die;
    (*data)->philo[i]->is_dead = (*data)->dead_mtx;
    (*data)->philo[i]->write_mtx = &(*data)->write_mtx;
    (*data)->philo[i]->fork = ft_malloc(sizeof(int), 1);
    *((*data)->philo[i]->fork) = 1; 
    (*data)->philo[i]->flag = (*data)->nbr_philo;
    (*data)->index = i;
    get_the_forks(&(*data)->philo[i], *data);
    init_philo((*data)->philo[i]);
}

int    create_philo(t_data *data)
{
    int     i;

    data->fork = ft_malloc(sizeof(pthread_mutex_t), data->nbr_philo);
    init_forks(data->fork, data->nbr_philo);
    data->philo = ft_malloc(sizeof(t_philo *), data->nbr_philo + 1);
    data->philo[data->nbr_philo] = NULL;
    data->dead_mtx = ft_malloc(sizeof(pthread_mutex_t), 1);
    pthread_mutex_init(data->dead_mtx, NULL);
    pthread_mutex_init(&data->write_mtx, NULL);
    data->is_dead = ft_malloc(sizeof(size_t), 3);
    ft_bzero(data->is_dead, sizeof(size_t));
    i = 0;
    while (i < data->nbr_philo)
    {
        fill_philo(&data, i);
        i++;
    }
    start_philo(data);
    create_monitor(data);
    join_every_thread(data);
    if (data->is_dead[2] == 1)
        print(data->philo[data->is_dead[0]], data->is_dead[1], 4);
    clear_all(data);
    return (1);
}
