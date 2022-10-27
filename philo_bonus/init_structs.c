/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:52:36 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:16:48 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_inits(t_philo *philo)
{
	philo->philo_name = -1;
	philo->time_to_start_eat = -1;
	philo->time_start = 0;
	sem_unlink("/print_sem");
	philo->print_sem = sem_open("/print_sem", O_CREAT, S_IWUSR, 1);
	if (philo->print_sem == SEM_FAILED)
		return (pserror("Error: system is not create print_sem"));
	sem_unlink("/fork_sem");
	philo->fork_sem = sem_open("/fork_sem", O_CREAT, S_IWUSR, \
		philo->num_of_philos);
	if (philo->fork_sem == SEM_FAILED)
		return (pserror("Error: system is not create fork_sem"));
	return (0);
}

int	check_valid_input(int argc, char **argv)
{
	int		arg;
	int		len;
	int		flag;

	if (argc < 5 || argc > 6)
		return (pserror("Error: Four or five argument only!"));
	flag = 0;
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0' || argv[arg][0] == '\0')
		{
			if (!('0' <= argv[arg][len] && argv[arg][len] <= '9') || len == 4)
			{
				printf("Error: Not valid argument %i\n", arg);
				flag = 1;
				break ;
			}
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	ft_parser(t_philo *philo, int argc, char **argv)
{
	if (check_valid_input(argc, argv))
		return (1);
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->times_each_must_eat = ft_atoi(argv[5]);
	else
		philo->times_each_must_eat = -1;
	return (0);
}
