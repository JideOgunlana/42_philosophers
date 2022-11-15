/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:19:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/15 21:46:06 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*monitor(void *arg)
{
	t_info		*info;
	t_monitor	monitor;

	info = (t_info *)arg;
	monitor.total_philos = info->total_philos;
	monitor.eat_limit = info->eat_limit * info->total_philos;
	monitor.end_eat = 0;
	monitor.end_simulation = 0;
	// printf("eat count: %d, eat_limit %d\n", info->eat_count, monitor.eat_limit);
	while (true)
	{
		if (ft_at_eat_limit(info, &monitor))
			break ;
		if (ft_is_any_philo_dead(info, &monitor))
			break ;
	}
	ft_kill_all_philos(info);
	if (monitor.end_simulation)
		printf("%lu %d is dead\n", monitor.end_time - info->start_time, \
		monitor.dead_philo_id + 1);
	return (NULL);
}

int	ft_at_eat_limit(t_info *info, t_monitor *monitor)
{
	pthread_mutex_lock(&(info->mutex));
	if (info->eat_count == monitor->eat_limit)
	{
		// printf("eat count: %d, eat_limit %d\n", info->eat_count, monitor->eat_limit);
		pthread_mutex_unlock(&(info->mutex));
		monitor->end_eat = 1;
		monitor->end_time = get_time();
		return (1);
	}
	pthread_mutex_unlock(&(info->mutex));
	return (0);
}

int	ft_is_any_philo_dead(t_info *info, t_monitor *monitor)
{
	int	philo_id;

	philo_id = -1;
	while (++philo_id < monitor->total_philos)
	{
		if (ft_is_philo_dead(info, philo_id) == DEAD)
		{
			monitor->dead_philo_id = philo_id;
			monitor->end_time = get_time();
			monitor->end_simulation = 1;
			return (1);
		}
	}
	return (0);
}

void	ft_kill_all_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_philos)
		info->philo_list[i] = DEAD;
	ft_usleep(1);
}
