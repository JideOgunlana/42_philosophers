/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:23:15 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/06 18:53:10 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_chopsticks_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		pthread_mutex_destroy(&info->chop_sticks[i]);
		i++;
	}
	return (0);
}

void	clean_up(pthread_t *threads, t_info *info, t_philos *philos)
{
	(void) philos;
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		pthread_detach(threads[i]);
		i++;
	}
	pthread_mutex_destroy(&info->mtx_end);
	destroy_chopsticks_mutex(info);
	free(info->chop_stick_status);
	free(info->chop_sticks);
	free(info);
	free(threads);
	// free(philos);
}

void	check_philo_state(t_philos *philo)
{
	if ((get_useconds() - philo->last_eat_time) / 1000 > (size_t)philo->info->time_to_die)
	{
		philo->info->philo_dies = 1;
		print_philo_status(philo, "died");
		pthread_mutex_lock(&philo->info->mtx_end);
	}
}

void	check_philos_death(t_philos *philo, t_info *info)
{
	int	i;

	while (!info->philo_dies)
	{
		ft_usleep(2 * 1000);
		i = 0;
		while (!info->philo_dies && i < info->philos_count)
		{
			check_philo_state(&philo[i]);
			i++;
		}
	}
	return ;
}