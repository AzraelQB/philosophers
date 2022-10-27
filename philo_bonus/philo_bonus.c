/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:52:24 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:16:39 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *tmp)
{
	t_philo	*philo;
	int		time_of_famine;

	philo = (t_philo *)tmp;
	while (1)
	{
		time_of_famine = (int)(time_in_ms() - philo->time_to_start_eat);
		if (time_of_famine > philo->time_to_die)
		{
			if (philo->times_each_must_eat != 0)
				philo_action(philo, "*dead");
			break ;
		}
	}
	exit(0);
}

void	wait_philo(t_philo *philo, int pid[])
{
	int		i;

	waitpid(-1, NULL, 0);
	if (philo->times_each_must_eat != 0)
	{
		i = -1;
		while (++i < philo->num_of_philos)
			kill(pid[i], SIGKILL);
	}
	else
	{
		i = -1;
		while (++i < philo->num_of_philos)
			waitpid(-1, NULL, 0);
	}
	sem_close(philo->print_sem);
	sem_unlink("/print_sem");
	sem_close(philo->fork_sem);
	sem_unlink("/fork_sem");
}

int	start_live(t_philo *philo, pthread_t *p_check_death)
{
	int		i;
	int		*pid;

	pid = malloc(sizeof(int) * philo->num_of_philos);
	philo->time_start = time_in_ms();
	i = -1;
	while (++i < philo->num_of_philos)
	{
		philo->philo_name = i + 1;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			pthread_create(p_check_death, NULL, check_death, philo);
			pthread_detach(*p_check_death);
			philo_life(philo);
			exit(0);
		}
		usleep(50);
	}
	wait_philo(philo, pid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	p_check_death;

	if (ft_parser(&philo, argc, argv))
		exit(1);
	if (ft_inits(&philo))
		exit(1);
	start_live(&philo, &p_check_death);
	exit(0);
}
