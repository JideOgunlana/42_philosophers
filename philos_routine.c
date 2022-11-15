/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:18:19 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/15 13:34:25 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_eating(t_info *info, t_philo *philo)
{
	while (ft_is_chop_stick_used(info, philo, 'l')
		|| ft_is_chop_stick_used(info, philo, 'r'))
	{
		// usleep(10);
		if (get_time() - philo->last_eat_time >= info->time_to_die)
		{
			ft_philo_died(info, philo);
			return (DEAD);
		}
		else if (ft_is_philo_dead(info, philo->id) == DEAD)
			return (DEAD);
	}
	pthread_mutex_lock(&(info->mutex));
	info->eat_count++;
	pthread_mutex_unlock(&(info->mutex));
	ft_print_info(philo, get_time(), EATING);
	philo->last_eat_time = get_time();
	ft_usleep(info->time_to_eat);
	ft_unlock_chop_sticks(info, philo, 'l');
	ft_unlock_chop_sticks(info, philo, 'r');
	return (0);
}

int	ft_sleeping(t_info *info, t_philo *philo)
{
	size_t	total_time;

	total_time = get_time() - philo->last_eat_time;
	if (ft_is_philo_dead(info, philo->id) == DEAD)
	{
		// printf("life time: %zu\n", total_time);
		return (DEAD);
	}
	if (total_time + info->time_to_sleep > info->time_to_die)
	{
		ft_print_info(philo, get_time(), SLEEPING);
		ft_usleep((info->time_to_die - total_time));
		ft_philo_died(info, philo);
		return (DEAD);
	}
	ft_print_info(philo, get_time(), SLEEPING);
	ft_usleep(info->time_to_sleep);
	return (0);
}

int	ft_thinking(t_info *info, t_philo *philo)
{
	if (ft_is_philo_dead(info, philo->id) == DEAD)
		return (DEAD);
	ft_print_info(philo, get_time(), THINKING);
	return (0);
}

void	*routine(void *arg)
{
	t_info	*info;
	t_philo	philo;

	info = (t_info *)arg;
	philo.id = ft_get_philo_position(info) - 1;
	ft_get_chop_stick_num(&philo, info);
	philo.start_time = info->start_time;
	philo.last_eat_time = philo.start_time;
	if (philo.id == 0 && info->total_philos == 1)
	{
		ft_lock_chop_sticks(info, &philo, 'r');
		ft_usleep(info->time_to_die);
		ft_kill_all_philos(info);
		return (NULL);
	}
	while (true)
	{
		if (ft_eating(info, &philo) == DEAD)
			break ;
		if (ft_sleeping(info, &philo) == DEAD)
			break ;
		if (ft_thinking(info, &philo) == DEAD)
			break ;
	}
	return (NULL);
}
