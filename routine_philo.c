/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:35:18 by salahian          #+#    #+#             */
/*   Updated: 2025/05/28 18:28:04 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(time_t time)
{
    time_t start;
    
    time = time / 1000;
    start = diff_time();
    while ((diff_time() - start) < time)
        usleep(100);
}

void    lock_the_forks(t_philo *philo)
{
    // if (philo->index % 2 != 0 && philo->flag % 2 == 0)
    //     usleep(500);
    if (philo->index % 2 == 0)
        usleep(100);
    pthread_mutex_lock(philo->right_fork);
    // if (philo->flag == 1)
    // {
    //     pthread_mutex_unlock(philo->right_fork);
    //     return ;
    // }
    if (check_is_dead(philo, 0))
    {
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    print(philo, diff_time(), 3); 
    pthread_mutex_lock(philo->left_fork);
    if (check_is_dead(philo, 0))
        return ;
    print(philo, diff_time(), 3);
    *(philo->fork) = 1;
}

// void lock_the_forks(t_philo *philo)
// {
//     if (philo->index % 2 == 0)
//     {
//         pthread_mutex_lock(philo->left_fork);
//         print(philo, diff_time(), 3);
//         if (check_is_dead(philo, 0))
//         {
//             pthread_mutex_unlock(philo->left_fork);
//             return ;
//         }
//         pthread_mutex_lock(philo->right_fork);
//         print(philo, diff_time(), 3);
//     }
//     else
//     {
//         pthread_mutex_lock(philo->right_fork);
//         print(philo, diff_time(), 3);
//         if (check_is_dead(philo, 0))
//         {
//             pthread_mutex_unlock(philo->right_fork);
//             return ;
//         }
//         pthread_mutex_lock(philo->left_fork);
//         print(philo, diff_time(), 3);
//     }
//     *(philo->fork) = 1;
// }


void    release_forks(t_philo *philo)
{
    if (*(philo->fork) != 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        *(philo->fork) = 0;
    }
}

void    print(t_philo *philo, time_t time, int flag)
{
    pthread_mutex_lock(&philo->write_mtx);
    if (flag == 0)
    {
        if (!check_is_dead(philo, 0))
            printf("%ld %d is eating\n", time, philo->index);
    }
    else if (flag == 1)
    {
        if (!check_is_dead(philo, 0))
            printf("%ld %d is sleeping\n", time, philo->index);
    }
    else if (flag == 2)
    {
        if (!check_is_dead(philo, 0))
            printf("%ld %d is thinking\n", time, philo->index);
    }
    else if (flag == 3)
    {
        if (!check_is_dead(philo, 0))
            printf("%ld %d has taken a fork\n", time, philo->index);
    }
    else
        printf("%ld %d died\n", time, philo->index);
    pthread_mutex_unlock(&philo->write_mtx);
}

void    eat_philo(t_philo *philo)
{
    if (philo->flag == 1)
        return ;
    lock_the_forks(philo);
    pthread_mutex_lock(&philo->last_meal_mtx);
    philo->last_meal = get_curr_time();
    pthread_mutex_unlock(&philo->last_meal_mtx);
    if (check_is_dead(philo, 0))
    {
        release_forks(philo);
        return ;
    }
    print(philo, diff_time(), 0);
    usleep(philo->t_eat * 1000);
    if (!philo->left_fork)
    {
        //release_forks(philo);
        return ;
    }
    release_forks(philo);
    //*(philo->fork) = 1;
}

void    sleep_philo(t_philo *philo)
{
    if (check_is_dead(philo, 0) || philo->flag == 1)
        return ;
    print(philo, diff_time(), 1);
    usleep(philo->t_sleep * 1000);
    
}

void    think_philo(t_philo *philo)
{
    time_t think;

    if (check_is_dead(philo, 0) || philo->flag == 1)
        return ;
    print(philo, diff_time(), 2);
    think = (philo->t_die - (diff_time() - philo->last_meal));
    think = (think * 0.7) * 1000;
    // if (philo->index % 2 != 0 && philo->flag % 2 == 0)
    usleep(500);
    // // else if (philo->index % 2 == 0)
    // //     usleep(500);
    
}

void    *start_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->flag == 1)
        print(philo, diff_time(), 3);
    while(check_is_dead(philo, 0) == 0)
    {
        if (!philo->left_fork)
            break ;
        eat_philo(philo);
        if (check_is_dead(philo, 0))
            break ;
        sleep_philo(philo);
        if (check_is_dead(philo, 0))
            break ;
        think_philo(philo);
    }
    return (NULL);
}
