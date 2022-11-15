/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:23:15 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/15 19:35:52 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	clean_up(t_info *info, pthread_t **philos)
{
	int	i;
	
	i = info->total_philos;
	while (i > 0)
	{
		pthread_mutex_destroy(&(info->philo_dead_mutex[i]));
		pthread_mutex_destroy(&(info->chop_sticks[i]));
		i--;
	}
	pthread_mutex_destroy(&(info->mutex));
	free(info->philo_list);
	free(info->philo_dead_mutex);
	free(info->using_chop_sticks);
	free(info->chop_sticks);
	free(*philos);
}

int	ft_is_philo_dead(t_info *info, int philo_id)
{
	if (info->philo_list[philo_id] == DEAD)
		return (DEAD);
	return (0);
}

int	ft_philo_died(t_info *info, t_philo *philo)
{
	info->philo_list[philo->id] = DEAD;
	return (DEAD);
}
