/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azrael <azrael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:43:14 by awooden           #+#    #+#             */
/*   Updated: 2022/10/26 22:55:01 by azrael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pserror(char *str)
{
	printf("%s\n", str);
	return (1);
}

long	time_in_ms(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

int	make_timestamp(t_info *info)
{
	int		time;

	time = (int)(time_in_ms() - info->time_start);
	if (time % 10 == 1)
		time--;
	return (time);
}

void	philo_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->f_exit == 0)
		printf("%i %i %s\n", make_timestamp(philo->info), \
			philo->philo_name, str);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

int	ft_atoi(const char *str)
{
	unsigned long long	sum;
	int					sign;

	sum = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || \
	*str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	if (sum > 9223372036854775807)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (sign * sum);
}
