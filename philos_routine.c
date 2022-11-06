/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:19:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/06 19:10:30 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philos *philo)
{
	// (void) philo;
	// printf("philo position: %d, philo count: %d\n",philo->position, philo->info->philos_count);
	while (true)
	{
		if (philo->info->chop_stick_status[philo->r_chop_stick] == FREE)
		{
			pthread_mutex_lock(&philo->info->chop_sticks[philo->r_chop_stick]);
			philo->info->chop_stick_status[philo->r_chop_stick] = LOCK;
			print_philo_status(philo, "has taken a fork");
			// printf("Philo %d has RIGHT fork\n", philo->position);
			pthread_mutex_lock(&philo->info->chop_sticks[philo->l_chop_stick]);
			philo->info->chop_stick_status[philo->l_chop_stick] = LOCK;
			print_philo_status(philo, "has taken a fork");
			philo->last_eat_time = get_useconds();
			print_philo_status(philo, "is eating");
			ft_usleep((philo->info->time_to_eat * 1000));
			// printf("Philo %d has LEFT fork\n", philo->position);
			// printf("Philo %d is EATING\n", philo->position);
			philo->info->chop_stick_status[philo->r_chop_stick] = FREE;
			philo->info->chop_stick_status[philo->l_chop_stick] = FREE;
			pthread_mutex_unlock(&philo->info->chop_sticks[philo->r_chop_stick]);
			pthread_mutex_unlock(&philo->info->chop_sticks[philo->l_chop_stick]);
			break ;
		}
		else
			usleep(100);
	}

}

void	philo_sleep(t_philos *philo)
{
	print_philo_status(philo, "is sleeping");
	ft_usleep((philo->info->time_to_sleep * 1000));
}

void	philo_think(t_philos *philo)
{
	print_philo_status(philo, "is thinking");
}
