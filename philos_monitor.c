/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:19:35 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/26 11:42:55 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*monitor(void *arg)
{
	t_info		*info;
	t_philo		philo;
	t_monitor	monitor;

	info = (t_info *)arg;
	monitor.total_philos = info->total_philos;
	monitor.eat_limit = info->eat_limit * info->total_philos;
	monitor.end_simulation = 0;
	while (true)
	{
		if (at_eat_limit(info, &monitor))
			break ;
		if (is_any_philo_dead(info, &monitor))
			break ;
	}
	kill_all_philos(info);
	if (monitor.end_simulation)
	{
		philo.start_time = info->start_time;
		philo.id = monitor.dead_philo_id;
		if (info->time_to_eat >= info->time_to_die)
			ms_sleep(info->time_to_die);
		ft_print_info(&philo, get_time_in_ms(), DEAD);
	}
	return (NULL);
}

int	at_eat_limit(t_info *info, t_monitor *monitor)
{
	pthread_mutex_lock(&(info->print_mutex));
	if (info->eat_count >= monitor->eat_limit && \
	monitor->eat_limit > 0)
	{
		pthread_mutex_unlock(&(info->print_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(info->print_mutex));
	return (0);
}

int	is_any_philo_dead(t_info *info, t_monitor *monitor)
{
	int	philo_id;

	philo_id = 0;
	while (philo_id < monitor->total_philos)
	{
		if (info->philo_list[philo_id] == DEAD)
		{
			pthread_mutex_lock(&info->print_mutex);
			info->pls_print = 0;
			monitor->dead_philo_id = philo_id;
			monitor->end_simulation = 1;
			pthread_mutex_unlock(&info->print_mutex);
			return (1);
		}
		philo_id++;
	}
	return (0);
}

void	kill_all_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_philos)
		info->philo_list[i] = DEAD;
	ms_sleep(2);
}
