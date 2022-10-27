/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:42:56 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:00:35 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philos(t_info *info, t_philo *philo)
{
	int		i;
	int		time_of_famine;

	while (1)
	{
		i = 0;
		while (i < info->num_of_philos)
		{
			time_of_famine = (int)(time_in_ms() - philo[i].time_to_start_eat);
			if (time_of_famine > info->time_to_die)
			{
				if (philo[i].times_each_must_eat != 0)
					philo_action(&philo[i], "dead");
				info->f_exit = 1;
				return ;
			}
			i++;
		}
	}
}

int	clean_philos(t_info *info, t_philo *philo)
{
	if (info->fork_mutex)
		free(info->fork_mutex);
	if (info->philo_threads)
		free(info->philo_threads);
	if (philo)
		free(philo);
	return (1);
}

void	end_philos(t_info *info, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(info->philo_threads[i], NULL);
	clean_philos(info, philo);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;
	int		i;

	if (parse_input(&info, argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * info.num_of_philos);
	if (!philo)
		return (pserror("Error: malloc: Inits philo structs"));
	if (init_structs(&info, philo))
		return (clean_philos(&info, philo));
	i = -1;
	info.time_start = time_in_ms();
	while (++i < info.num_of_philos)
	{
		if (pthread_create(&info.philo_threads[i], NULL, philo_life, &philo[i]))
		{
			clean_philos(&info, philo);
			return (pserror("Error: System did not create philo_threads"));
		}
		usleep(50);
	}
	check_philos(&info, philo);
	end_philos(&info, philo);
	return (0);
}
