/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:35:18 by salahian          #+#    #+#             */
/*   Updated: 2025/05/29 17:07:52 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(t_philo *philo, size_t time)
{
    size_t start;
    
    start = get_curr_time();
    while ((get_curr_time() - start) < time)
    {
        if (check_is_dead(philo, 0))
            return ;
        usleep(50);
    }
}

void    release_forks(t_philo *philo)
{
    if (*(philo->fork) != 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_lock(&philo->fork_mtx);
        *(philo->fork) = 0;
        pthread_mutex_unlock(&philo->fork_mtx);
    }
}

void    print(t_philo *philo, time_t time, int flag)
{
    pthread_mutex_lock(philo->write_mtx);
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
    pthread_mutex_unlock(philo->write_mtx);
}

void    lock_the_forks(t_philo *philo)
{
    if (philo->index % 2 == 0 && philo->flag % 2 == 0)
        usleep(100);
    pthread_mutex_lock(philo->right_fork);
    if (check_is_dead(philo, 0))
    {
        pthread_mutex_lock(&philo->fork_mtx);
        *(philo->fork) = 0;
        pthread_mutex_unlock(&philo->fork_mtx);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    print(philo, diff_time(), 3); 
    pthread_mutex_lock(philo->left_fork);
    // if (check_is_dead(philo, 0))
    // {
    //     //*(philo->fork) = 1;
    //     release_forks(philo);
    //     return ;
    // }
    print(philo, diff_time(), 3);
    pthread_mutex_lock(&philo->fork_mtx);
    *(philo->fork) = 1;
    pthread_mutex_unlock(&philo->fork_mtx);
}

void    eat_philo(t_philo *philo)
{
    if (philo->flag == 1)
        return ;
    lock_the_forks(philo);
    // if (check_is_dead(philo, 0))
    // {
    //     release_forks(philo);
    //     return ;
    // }
    pthread_mutex_lock(&philo->last_meal_mtx);
    philo->last_meal = get_curr_time();
    philo->nbr_of_meal--;
    pthread_mutex_unlock(&philo->last_meal_mtx);
    // if (check_is_dead(philo, 0))
    // {
    //     release_forks(philo);
    //     return ;
    // }
    print(philo, diff_time(), 0);
    ft_usleep(philo, philo->t_eat);
    //usleep(philo->t_eat * 1000);
    release_forks(philo);
    if (check_is_dead(philo, 0))
    {
        // release_forks(philo);
        return ;
    }
}

void    sleep_philo(t_philo *philo)
{
    if (check_is_dead(philo, 0) || philo->flag == 1)
        return ;
    print(philo, diff_time(), 1);
    ft_usleep(philo, philo->t_sleep);
    //usleep(philo->t_sleep * 1000);
    
}

void    think_philo(t_philo *philo)
{
    if (check_is_dead(philo, 0) || philo->flag == 1)
        return ;
    print(philo, diff_time(), 2);
    usleep(400);
    // // else if (philo->index % 2 == 0)
    // //     usleep(500);
    
}

void    *start_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->flag == 1 && philo->nbr_of_meal != 0)
        print(philo, diff_time(), 3);
    while(check_is_dead(philo, 0) == 0)
    {
        if (check_is_dead(philo, 0) || !philo->nbr_of_meal)
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
