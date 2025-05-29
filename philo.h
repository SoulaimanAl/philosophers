/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:58:51 by salahian          #+#    #+#             */
/*   Updated: 2025/05/29 17:07:34 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_garbag
{
	void			*addr;
	struct s_garbag	*next;
}					t_gar;

typedef struct s_philo
{
	size_t			t_eat;
	size_t			t_sleep;
	size_t			t_die;
	int				index;
	time_t			last_meal;
	size_t			nbr_of_meal;
    int     *fork;
	int		flag;
    pthread_mutex_t	fork_mtx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*is_dead;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	*write_mtx;
	pthread_t		philo;
}					t_philo;

typedef struct s_data
{
	size_t			t_eat;
	size_t			t_sleep;
	size_t			t_die;
	int				nbr_philo;
	size_t			nbr_of_meal;
	int				index;
	size_t				*is_dead;
	pthread_t		monitor;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	*dead_mtx;
	t_philo			**philo;
}					t_data;

int				create_philo(t_data *data);
void				*start_routine(void *arg);
void				*check_philos(void *arg);

/// functions_helper
void    release_forks(t_philo *philo);
int					check_is_dead(t_philo *philo, int nbr);
int					ft_atoi(const char *str, int *flag);
void				ft_bzero(void *s, size_t n);
time_t				get_curr_time(void);
void				init_philo(t_philo *philo);
void				init_forks(pthread_mutex_t *fork, int nbr);
void				print(t_philo *philo, time_t time, int flag);

/// clean
void				*ft_malloc(int size, int bytes);
void				ft_lstclear(t_gar **lst);
t_gar				**garbage_list(void);
time_t				diff_time(void);

#endif
