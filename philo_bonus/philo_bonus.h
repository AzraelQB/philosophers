/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:52:18 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 23:16:12 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define S_IWUSR 0000200
# define O_CREAT 0x0200

typedef struct s_philo
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_must_eat;
	int				philo_name;
	long			time_to_start_eat;
	long			time_start;
	sem_t			*print_sem;
	sem_t			*fork_sem;
}				t_philo;

int				ft_parser(t_philo *philo, int argc, char **argv);
int				ft_inits(t_philo *philo);
void			*philo_life(void *tmp);
int				pserror(char *str);
long			time_in_ms(void);
void			philo_action(t_philo *philo, char *str);
int				ft_atoi(const char *str);

#endif
