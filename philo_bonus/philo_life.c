/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:52:32 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:16:29 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_work(int timer)
{
	long	start_time;

	start_time = time_in_ms();
	usleep(timer * 1000 - 7000);
	while (time_in_ms() - start_time < timer)
		usleep(100);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->fork_sem);
	sem_wait(philo->fork_sem);
	philo_action(philo, "has taken a fork");
	philo_action(philo, "has taken a fork");
	philo->time_to_start_eat = time_in_ms();
	philo_action(philo, "is eating");
	time_work(philo->time_to_eat);
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
}

void	*philo_life(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	philo->time_to_start_eat = time_in_ms();
	while (philo->times_each_must_eat != 0)
	{
		if (philo->num_of_philos == 1)
			return (NULL);
		take_fork(philo);
		philo_action(philo, "is sleeping");
		time_work(philo->time_to_sleep);
		philo_action(philo, "is thinking");
		if (philo->times_each_must_eat != -1)
			philo->times_each_must_eat--;
		if (philo->times_each_must_eat == 0)
		{
			sem_wait(philo->print_sem);
			exit(0);
		}
	}
	return (0);
}
