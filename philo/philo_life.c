/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:42:56 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:00:48 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_work(int timer)
{
	long	start_time;

	start_time = time_in_ms();
	usleep(timer * 1000 - 7000);
	while (time_in_ms() - start_time < timer)
		usleep(100);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	philo_action(philo, "has taken a fork");
	philo_action(philo, "has taken a fork");
	philo->time_to_start_eat = time_in_ms();
	philo_action(philo, "is eating");
	time_work(philo->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*philo_life(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	philo->time_to_start_eat = time_in_ms();
	while (philo->times_each_must_eat != 0)
	{
		if (philo->info->num_of_philos == 1)
			return (NULL);
		philo_eat(philo);
		philo_action(philo, "is sleeping");
		time_work(philo->time_to_sleep);
		philo_action(philo, "is thinking");
		if (philo->times_each_must_eat != -1)
			philo->times_each_must_eat--;
		if (philo->info->f_exit == 1)
			break ;
	}
	return (0);
}
