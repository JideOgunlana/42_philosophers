/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:53:36 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/24 17:49:53 by bogunlan         ###   ########.fr       */
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

int	get_philo_position(t_info *info)
{
	int	position;

	pthread_mutex_lock(&(info->read_shared_var));
	info->count_philos += 1;
	if (info->count_philos > info->total_philos)
		info->count_philos = 1;
	position = info->count_philos;
	pthread_mutex_unlock(&(info->read_shared_var));
	return (position);
}


void	ft_print_info(t_philo *philo, size_t current_time, int c)
{
	if (c == EATING /* && philo->pls_print */)
		printf("%lu %d is eating\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == SLEEPING /* && philo->pls_print */)
		printf("%lu %d is sleeping\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == THINKING /* && philo->pls_print */)
		printf("%lu %d is thinking\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == DEAD)
		printf("%lu %d is dead\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == LEFT /* && philo->pls_print */)
		printf("%lu %d has taken the left fork\n", current_time - philo->start_time, \
		philo->id + 1);
	else if (c == RIGHT /* && philo->pls_print */)
		printf("%lu %d has taken the right fork\n", current_time - philo->start_time, \
		philo->id + 1);
}
