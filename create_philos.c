/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:13:11 by salahian          #+#    #+#             */
/*   Updated: 2025/05/28 17:02:20 by salahian         ###   ########.fr       */
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
/*
t_philo

ID
pthred
int fork
fork_look
last_meal_look
num_of_meals
t_philo *left
t_philo *right
*/
void    get_the_forks(t_philo **philo, t_data *data)
{
    // if (data->nbr_philo == 1)
    // {
    //     (*philo)->right_fork = &(data->fork[0]);
    //     (*philo)->left_fork = NULL;
    // }
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

void    clear_all(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nbr_philo)
    {
        //pthread_mutex_destroy(&data->fork[i]);
        //if (data->philo[i]->right_fork)
            //pthread_mutex_destroy(data->philo[i]->right_fork);
        //if (data->philo[i]->left_fork)
           // pthread_mutex_destroy(data->philo[i]->left_fork);
        pthread_mutex_destroy(&data->philo[i]->last_meal_mtx);
        pthread_mutex_destroy(data->philo[i]->is_dead);
        i++;
    }
    ft_lstclear(garbage_list());
}

void    create_philo(t_data *data)
{
    int     i;

    data->fork = ft_malloc(sizeof(pthread_mutex_t), data->nbr_philo);
    init_forks(data->fork, data->nbr_philo);
    data->philo = ft_malloc(sizeof(t_philo *), data->nbr_philo + 1);
    data->philo[data->nbr_philo] = NULL;
    data->dead_mtx = ft_malloc(sizeof(pthread_mutex_t), 1);
    pthread_mutex_init(data->dead_mtx, NULL);
    i = 0;
    while (i < data->nbr_philo)
    {
        data->philo[i] = ft_malloc(sizeof(t_philo), 1);
        data->philo[i]->index = i + 1;
        data->philo[i]->t_eat = data->t_eat;
        data->philo[i]->t_sleep = data->t_sleep;
        data->philo[i]->nbr_of_meal = data->nbr_of_meal;
        data->philo[i]->t_die = data->t_die;
        data->philo[i]->is_dead = data->dead_mtx;
        data->philo[i]->fork = ft_malloc(sizeof(int), 1);
        *(data->philo[i]->fork) = 1; 
        data->philo[i]->flag = data->nbr_philo;
        data->index = i;
        get_the_forks(&data->philo[i], data);
        init_philo(data->philo[i]);
        i++;
    }
    start_philo(data);
    create_monitor(data);
    join_every_thread(data);
    clear_all(data);
}

// create array of forks // if the number is odd will take the right will be index and left index - 1 and reverse for other number
// create the function routine will call eat sleep think
// for eat will call take forks and lock the 2 of them and lock the eat means sleep time and unlock everything
// for sleep will sleep
// for think will sleep the 70% of t_die - get_current_time - last_meal of philo
// create function moniteuring that loops on every thread to check if he die, if true will stop