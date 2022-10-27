/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:43:22 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 22:54:24 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_must_eat;
	pthread_t		*philo_threads;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	int				f_exit;
	long			time_start;
}				t_info;

typedef struct s_philo
{
	int				philo_name;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_must_eat;
	long			time_to_start_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_info			*info;
}				t_philo;

int				parse_input(t_info *info, int argc, char **argv);
int				init_structs(t_info *info, t_philo *philo);

void			*philo_life(void *tmp);
void			philo_action(t_philo *philo, char *str);

long			time_in_ms(void);
int				ft_atoi(const char *str);
int				pserror(char *str);

#endif
