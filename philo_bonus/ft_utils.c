/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:52:29 by awooden           #+#    #+#             */
/*   Updated: 2022/06/28 23:37:03 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	make_timestamp(t_philo *philo)
{
	int		time;

	time = (int)(time_in_ms() - philo->time_start);
	if (time % 10 != 0)
		time -= time % 10;
	return (time);
}

void	philo_action(t_philo *philo, char *str)
{
	sem_wait(philo->print_sem);
	if (str[0] == '*')
	{
		printf("%i %i %s\n", make_timestamp(philo), philo->philo_name, ++str);
		return ;
	}
	printf("%i %i %s\n", make_timestamp(philo), philo->philo_name, str);
	sem_post(philo->print_sem);
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
