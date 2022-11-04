/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:19:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/03 16:10:51 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test(int i)
{
	t_philos *philos = all();

	if (philos[(i + philos[i].info->philos_count) % philos[i].info->philos_count].state != EATING
		&& philos[(i + 1) % philos[i].info->philos_count].state != EATING
		&& philos[i].state == THINKING
	)
	{
		philos[i].state = EATING;
		// printf("Philo %d is %d\n", philos[i].position, philos[i].state);
		pthread_mutex_lock(&philos[i].info->chop_sticks[philos[i].r_chop_stick]);
		philos[i].info->chop_stick_status[philos[i].r_chop_stick] = LOCK;
		printf("Philo %d has taken the right fork\n", philos[i].position);
		pthread_mutex_lock(&philos->info->chop_sticks[philos[i].l_chop_stick]);
		philos[i].info->chop_stick_status[philos[i].l_chop_stick] = LOCK;
		printf("Philo %d has taken the left fork\n", philos[i].position);
		printf("Philo %d is eating\n", philos[i].position);
	}
}

void	pick_up(int i)
{
	t_philos *philos = all();

	philos[i].state = THINKING;
	test(i);
	if (philos[i].state != EATING)
	{
		philos[i].state = THINKING;
	}
}

void	put_down(int i)
{
	t_philos	*philos = all();

	philos[i].state = SLEEPING;
	pthread_mutex_unlock(&philos[i].info->chop_sticks[philos[i].r_chop_stick]);
	pthread_mutex_unlock(&philos[i].info->chop_sticks[philos[i].l_chop_stick]);
	philos[i].info->chop_stick_status[philos[i].r_chop_stick] = FREE;
	philos[i].info->chop_stick_status[philos[i].l_chop_stick] = FREE;
	printf("Philo %d is sleeping\n", philos[i].position);
	test((i + philos[i].info->philos_count - 1) % philos[i].info->philos_count);
	test((i + 1) % philos[i].info->philos_count);
}

void	philo_eat(int i)
{
/* 	t_philos *philos = all();
	printf("philos position: %d, philos count: %d\n",philos[i].position, philos[i].info->philos_count);
	if (philos[i].info->chop_stick_status[philos[i].r_chop_stick] == FREE
		// && philos[i].info->chop_stick_status[philos->l_chop_stick] == FREE
	)
	{
		pthread_mutex_lock(&philos[i].info->chop_sticks[philos[i].r_chop_stick]);
		philos[i].info->chop_stick_status[philos[i].r_chop_stick] = LOCK;
		printf("Philo %d has taken a fork\n", philos->position);
		pthread_mutex_lock(&philos[i].info->chop_sticks[philos[i].l_chop_stick]);
		philos[i].info->chop_stick_status[philos[i].l_chop_stick] = LOCK;
		printf("Philo %d has taken a fork\n", philos->position);
		printf("Philo %d is eating\n", philos->position);
		pthread_mutex_unlock(&philos[i].info->chop_sticks[philos[i].r_chop_stick]);
		pthread_mutex_unlock(&philos[i].info->chop_sticks[philos[i].l_chop_stick]);
		philos[i].info->chop_stick_status[philos[i].r_chop_stick] = FREE;
		philos[i].info->chop_stick_status[philos[i].l_chop_stick] = FREE;
	} */
	while (true)
	{
		// printf("**%d**\n", i);
		sleep(4);
		pick_up(i);
		put_down(i);
	}
}

void	philo_sleep(t_philos *philos)
{
	(void) philos;

	// printf("Philo %d is sleeping\n", philos->position);
	// usleep(1000);
}

void	philo_think(t_philos *philos)
{
	(void) philos;

	// printf("Philo %d is thinking\n", philos->position);
	// usleep(1000);
}