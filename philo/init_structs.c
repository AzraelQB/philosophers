/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:43:10 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:01:01 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	inits_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
	{
		philo[i].philo_name = i + 1;
		philo[i].time_to_die = info->time_to_die;
		philo[i].time_to_eat = info->time_to_eat;
		philo[i].time_to_sleep = info->time_to_sleep;
		philo[i].times_each_must_eat = info->times_each_must_eat;
		philo[i].left = &info->fork_mutex[i];
		philo[i].right = &info->fork_mutex[(i + 1) % info->num_of_philos];
		philo[i].time_to_start_eat = -1;
		philo[i].info = info;
	}
}

int	init_fork(t_info *info)
{
	int			i;

	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (!info->fork_mutex)
		return (pserror("Error: malloc: inits fork_mutex"));
	i = -1;
	while (++i < info->num_of_philos)
		if (pthread_mutex_init(&info->fork_mutex[i], NULL))
			return (pserror("Error: system did not create fork_mutex"));
	return (0);
}

int	init_structs(t_info *info, t_philo *philo)
{
	info->philo_threads = malloc(sizeof(pthread_t) * info->num_of_philos);
	if (!info->philo_threads)
		return (pserror("Error: malloc: inits philo_threads"));
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (pserror("Error: system did not create print_mutex"));
	if (init_fork(info))
		return (1);
	inits_philo(info, philo);
	info->time_start = 0;
	info->f_exit = 0;
	return (0);
}

int	check_valid_input(int argc, char **argv)
{
	int		arg;
	int		len;

	if (argc < 5 || argc > 6)
		return (pserror("Error: Four or five arguments only!"));
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0' || argv[arg][0] == '\0')
			if (!('0' <= argv[arg][len] && argv[arg][len] <= '9') || len == 4)
				return (pserror("Error: Non-valid argument"));
	}
	return (0);
}

int	parse_input(t_info *info, int argc, char **argv)
{
	if (check_valid_input(argc, argv))
		return (1);
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->num_of_philos <= 0 || info->time_to_die <= 0 || \
		info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (pserror("Error: Non-valid input"));
	if (argc == 6)
	{
		info->times_each_must_eat = ft_atoi(argv[5]);
		if (info->times_each_must_eat <= 0)
			return (pserror("Error: Non-valid input"));
	}
	else
		info->times_each_must_eat = -1;
	return (0);
}
