/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:53:36 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/15 14:43:03 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

size_t	ft_get_philo_position(t_info *info)
{
	size_t	position;

	pthread_mutex_lock(&(info->mutex));
	info->count_philos += 1;
	if (info->count_philos > info->total_philos)
		info->count_philos = 1;
	position = info->count_philos;
	pthread_mutex_unlock(&(info->mutex));
	return (position);
}

void	ft_get_chop_stick_num(t_philo *philo, t_info *info)
{
	if (philo->id == 0)
		philo->l_chop_stick = info->total_philos - 1;
	else
		philo->l_chop_stick = philo->id - 1;
	philo->r_chop_stick = philo->id;
}

void	ft_print_info(t_philo *philo, size_t current_time, int c)
{
	if (c == EATING)
		printf("%lu %d is eating\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == SLEEPING)
		printf("%lu %d is sleeping\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == THINKING)
		printf("%lu %d is thinking\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == DEAD)
		printf("%lu %d is dead\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == CHOP_STICK_TAKEN)
		printf("%lu %d  has taken a fork\n", current_time - philo->start_time, \
		philo->id + 1);
}
