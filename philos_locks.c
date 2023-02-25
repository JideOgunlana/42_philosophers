/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_locks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:30:41 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/21 19:45:17 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

/* int	ft_is_chop_stick_used(t_info *info, t_philo *philo, char c)
{
	if (c == 'l' && philo->lcs != 1)
	{
		pthread_mutex_lock(&(info->chop_sticks[philo->l_chop_stick]));
		if (info->chop_stick_status[philo->l_chop_stick] != 0)
		{
			pthread_mutex_unlock(&(info->chop_sticks[philo->l_chop_stick]));
			return (1);
		}
		ft_lock_chop_sticks(info, philo, 'l');
		pthread_mutex_unlock(&(info->chop_sticks[philo->l_chop_stick]));
	}
	else if (c == 'r' && philo->rcs != 1)
	{
		pthread_mutex_lock(&(info->chop_sticks[philo->r_chop_stick]));
		if (info->chop_stick_status[philo->r_chop_stick] != 0)
		{
			pthread_mutex_unlock(&(info->chop_sticks[philo->r_chop_stick]));
			return (1);
		}
		ft_lock_chop_sticks(info, philo, 'r');
		pthread_mutex_unlock(&(info->chop_sticks[philo->r_chop_stick]));
	}
	return (0);
}

int	ft_lock_chop_sticks(t_info *info, t_philo *philo, char c)
{
	if (c == 'r')
	{
		info->chop_stick_status[philo->r_chop_stick] = 1;
		philo->rcs = 1;
		ft_print_info(philo, get_time_in_ms(), CHOP_STICK_TAKEN);
	}
	else if (c == 'l')
	{
		info->chop_stick_status[philo->l_chop_stick] = 1;
		philo->lcs = 1;
		ft_print_info(philo, get_time_in_ms(), CHOP_STICK_TAKEN);
	}
	return (0);
}

void	ft_unlock_chop_sticks(t_info *info, t_philo *philo, char c)
{
	if (c == 'r')
	{
		philo->rcs = 0;
		pthread_mutex_lock(&(info->chop_sticks[philo->r_chop_stick]));
		info->chop_stick_status[philo->r_chop_stick] = 0;
		pthread_mutex_unlock(&(info->chop_sticks[philo->r_chop_stick]));
	}
	else if (c == 'l')
	{
		philo->lcs = 0;
		pthread_mutex_lock(&(info->chop_sticks[philo->l_chop_stick]));
		info->chop_stick_status[philo->l_chop_stick] = 0;
		pthread_mutex_unlock(&(info->chop_sticks[philo->l_chop_stick]));
	}
}
 */