/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:18:19 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/27 06:42:07 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	eating(t_info *info, t_philo *philo)
{
	while (info->chop_stick_status[philo->id] == 1 && \
		info->chop_stick_status[(philo->id + 1) % info->total_philos] == 1)
	{
		check_philo_status(info, philo);
		if (philo->philo_status == DEAD)
			return (DEAD);
	}
	if (philo->id % 2 == 0)
		even_seated_philos_routine(info, philo);
	else
		odd_seated_philos_routine(info, philo);
	pthread_mutex_unlock(&info->chop_sticks[(philo->id + 1) % \
	info->total_philos]);
	pthread_mutex_unlock(&info->chop_sticks[philo->id]);
	info->chop_stick_status[(philo->id + 1) % info->total_philos] = 0;
	info->chop_stick_status[philo->id] = 0;
	return (0);
}

int	sleeping(t_info *info, t_philo *philo)
{
	size_t	last_eat_time;

	last_eat_time = get_time_in_ms() - philo->last_eat_time;
	if (info->philo_list[philo->id] == DEAD)
		return (DEAD);
	if (last_eat_time + info->time_to_sleep >= info->time_to_die)
	{
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
			ft_print_info(philo, get_time_in_ms(), SLEEPING);
		pthread_mutex_unlock(&info->print_mutex);
		ms_sleep((info->time_to_die - last_eat_time));
		info->philo_list[philo->id] = DEAD;
		philo->philo_status = DEAD;
		return (DEAD);
	}
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
		ft_print_info(philo, get_time_in_ms(), SLEEPING);
	pthread_mutex_unlock(&info->print_mutex);
	ms_sleep(info->time_to_sleep);
	return (0);
}

int	thinking(t_info *info, t_philo *philo)
{
	if (info->philo_list[philo->id] == DEAD)
		return (DEAD);
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
		ft_print_info(philo, get_time_in_ms(), THINKING);
	pthread_mutex_unlock(&info->print_mutex);
	return (0);
}

void	only_one_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->chop_sticks[philo->id]);
	printf("%lu Philo %d has taken a fork\n", get_time_in_ms() - \
	philo->last_eat_time, philo->id + 1);
	ms_sleep(info->time_to_die);
	pthread_mutex_unlock(&info->chop_sticks[philo->id]);
	kill_all_philos(info);
}

void	*routine(void *arg)
{
	t_info	*info;
	t_philo	philo;

	info = (t_info *)arg;
	philo.id = get_philo_position(info) - 1;
	info->start_time = get_time_in_ms();
	philo.start_time = info->start_time;
	philo.last_eat_time = philo.start_time;
	if (philo.id == 0 && info->total_philos == 1)
		only_one_philo(info, &philo);
	else
	{
		while (true)
		{
			if (eating(info, &philo) == DEAD)
				break ;
			if (sleeping(info, &philo) == DEAD)
				break ;
			if (thinking(info, &philo) == DEAD)
				break ;
		}
	}
	return (NULL);
}
