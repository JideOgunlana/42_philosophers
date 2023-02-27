/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_locks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:30:41 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/27 05:09:19 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	check_philo_status(t_info *info, t_philo *philo)
{
	if (get_time_in_ms() - philo->last_eat_time >= info->time_to_die)
	{
		info->philo_list[philo->id] = DEAD;
		philo->philo_status = DEAD;
	}
	else if (info->time_to_eat * info->total_philos >= info->time_to_die && \
	info->total_philos % 2 != 0)
	{
				philo->philo_status = DEAD;
	}
	else if (info->philo_list[philo->id] == DEAD)
	{
		philo->philo_status = DEAD;
	}
}

void	pick_left_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
		ft_print_info(philo, get_time_in_ms(), LEFT);
	pthread_mutex_unlock(&info->print_mutex);
	info->chop_stick_status[(philo->id + 1) % info->total_philos] = 1;
}

void	print_eating(t_info *info, t_philo *philo)
{
	if (info->pls_print)
	{
		if (info->time_to_eat >= info->time_to_die)
		{
			info->philo_list[philo->id] = DEAD;
			philo->philo_status = DEAD;
		}
		ft_print_info(philo, get_time_in_ms(), EATING);
	}
}

void	even_seated_philos_routine(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->chop_sticks[(philo->id+1) % info->total_philos]);
	pick_left_fork(info, philo);
	info->chop_stick_status[(philo->id + 1) % info->total_philos] = 1;
	check_philo_status(info, philo);
	if (philo->philo_status == DEAD)
		return ;
	pthread_mutex_lock(&info->chop_sticks[philo->id]);
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
		ft_print_info(philo, get_time_in_ms(), RIGHT);
	pthread_mutex_unlock(&info->print_mutex);
	info->chop_stick_status[philo->id] = 1;
	pthread_mutex_lock(&(info->read_shared_var));
	info->eat_count++;
	pthread_mutex_lock(&info->print_mutex);
	print_eating(info, philo);
	pthread_mutex_unlock(&info->print_mutex);
	pthread_mutex_unlock(&(info->read_shared_var));
	philo->last_eat_time = get_time_in_ms();
	ms_sleep(info->time_to_eat);
}

void	odd_seated_philos_routine(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->chop_sticks[philo->id]);
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
		ft_print_info(philo, get_time_in_ms(), RIGHT);
	pthread_mutex_unlock(&info->print_mutex);
	info->chop_stick_status[philo->id] = 1;
	check_philo_status(info, philo);
	if (philo->philo_status == DEAD)
		return ;
	pthread_mutex_lock(&info->chop_sticks[(philo->id + 1) % info->total_philos]);
	pick_left_fork(info, philo);
	pthread_mutex_lock(&(info->read_shared_var));
	info->eat_count++;
	pthread_mutex_lock(&info->print_mutex);
	print_eating(info, philo);
	pthread_mutex_unlock(&info->print_mutex);
	pthread_mutex_unlock(&(info->read_shared_var));
	philo->last_eat_time = get_time_in_ms();
	ms_sleep(info->time_to_eat);
}
