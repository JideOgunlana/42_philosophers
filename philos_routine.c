/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:18:19 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/25 05:56:41 by bogunlan         ###   ########.fr       */
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
	else if (info->philo_list[philo->id] == DEAD)
		philo->philo_status = DEAD;
}

int	eating(t_info *info, t_philo *philo)
{
	while (info->chop_stick_status[philo->id] == 1 || \
		info->chop_stick_status[(philo->id + 1)%info->total_philos] == 1)
	{
		check_philo_status(info, philo);
		if (philo->philo_status == DEAD)
			return (DEAD);
	}

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&info->chop_sticks[(philo->id+1)%info->total_philos]);
		if ((philo->id + 1)%info->total_philos == 0)
		{
			pthread_mutex_lock(&info->print_mutex);
			if (info->pls_print)
			{
				// printf("State of print eating fxn 1:%d:\n", info->pls_print);
				ft_print_info(philo, get_time_in_ms(), LEFT);
				// printf("%lu Philo %d has taken fork %d, the LEFT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, ((philo->id + 1)%info->total_philos) + info->total_philos);
			}
			pthread_mutex_unlock(&info->print_mutex);
		}
		else
		{
			pthread_mutex_lock(&info->print_mutex);
			if (info->pls_print)
			{
				// printf("State of print eating fxn 2:%d:\n", info->pls_print);
				ft_print_info(philo, get_time_in_ms(), LEFT);
				// printf("%lu Philo %d has taken fork %d, the LEFT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, (philo->id + 1)%info->total_philos);
			}
			pthread_mutex_unlock(&info->print_mutex);
		}
		info->chop_stick_status[(philo->id + 1)%info->total_philos] = 1;
		pthread_mutex_lock(&info->chop_sticks[philo->id]);
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
		{
			// printf("State of print eating fxn 3:%d:\n", info->pls_print);
				ft_print_info(philo, get_time_in_ms(), RIGHT);
			// printf("%lu Philo %d has taken fork %d, the RIGHT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, philo->id);
		}
		pthread_mutex_unlock(&info->print_mutex);
		info->chop_stick_status[philo->id] = 1;
		pthread_mutex_lock(&(info->read_shared_var));
		info->eat_count++;
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
		{
			if (info->time_to_eat >= info->time_to_die)
			{
				info->philo_list[philo->id] = DEAD;
				philo->philo_status = DEAD;
			}
			// printf("State of print eating fxn 4:%d:\n", info->pls_print);
			ft_print_info(philo, get_time_in_ms(), EATING);
		}
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_unlock(&(info->read_shared_var));
		philo->last_eat_time = get_time_in_ms();
		ms_sleep(info->time_to_eat);
	}
	else
	{
		pthread_mutex_lock(&info->chop_sticks[philo->id]);
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
		{
			// printf("State of print eating fxn 5:%d:\n", info->pls_print);
			ft_print_info(philo, get_time_in_ms(), RIGHT);
			// printf("%lu Philo %d has taken fork %d, the RIGHT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, philo->id);
		}
		pthread_mutex_unlock(&info->print_mutex);
		info->chop_stick_status[philo->id] = 1;
		pthread_mutex_lock(&info->chop_sticks[(philo->id+1)%info->total_philos]);
		if ((philo->id + 1)%info->total_philos == 0)
		{
			pthread_mutex_lock(&info->print_mutex);
			if (info->pls_print)
			{
				// printf("State of print eating fxn 6:%d:\n", info->pls_print);
				ft_print_info(philo, get_time_in_ms(), LEFT);
				// printf("%lu Philo %d has taken fork %d, the LEFT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, ((philo->id + 1)%info->total_philos) + info->total_philos);
			}
			pthread_mutex_unlock(&info->print_mutex);
		}
		else
		{
			pthread_mutex_lock(&info->print_mutex);
			if (info->pls_print)
			{
				// printf("State of print eating fxn 7:%d:\n", info->pls_print);
				ft_print_info(philo, get_time_in_ms(), LEFT);
				// printf("%lu Philo %d has taken fork %d, the LEFT fork\n", get_time_in_ms() - philo->last_eat_time, philo->id + 1, (philo->id + 1)%info->total_philos);
			}
			pthread_mutex_unlock(&info->print_mutex);
		}
		info->chop_stick_status[(philo->id + 1)%info->total_philos] = 1;
		pthread_mutex_lock(&(info->read_shared_var));
		info->eat_count++;
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
		{
			// printf("State of print eating fxn 8:%d:\n", info->pls_print);
			if (info->time_to_eat >= info->time_to_die)
			{
				info->philo_list[philo->id] = DEAD;
				philo->philo_status = DEAD;
			}
			ft_print_info(philo, get_time_in_ms(), EATING);
		}
		pthread_mutex_unlock(&info->print_mutex);
		pthread_mutex_unlock(&(info->read_shared_var));
		philo->last_eat_time = get_time_in_ms();
		ms_sleep(info->time_to_eat);
	}
	pthread_mutex_unlock(&info->chop_sticks[philo->id]);
	info->chop_stick_status[philo->id] = 0;
	pthread_mutex_unlock(&info->chop_sticks[(philo->id+1)%info->total_philos]);
	info->chop_stick_status[(philo->id + 1)%info->total_philos] = 0;
	return (0);
}

int	sleeping(t_info *info, t_philo *philo)
{
	size_t	total_time;

	total_time = get_time_in_ms() - philo->last_eat_time;
	if (info->philo_list[philo->id] == DEAD)
	{
		return (DEAD);
	}
	if (total_time + info->time_to_sleep >= info->time_to_die)
	{
		pthread_mutex_lock(&info->print_mutex);
		if (info->pls_print)
		{
			// printf("State of print sleeping fxn 1:%d:\n", info->pls_print);
			ft_print_info(philo, get_time_in_ms(), SLEEPING);
		}
		pthread_mutex_unlock(&info->print_mutex);
		// if (info->total_philos % 2 == 0 && \ this part of code is not needed because a philo should die when it does not start eating since the beginning of the last meal
		// info->time_to_eat >= info->time_to_sleep)
		// 	ms_sleep(info->time_to_sleep);
		// else
			ms_sleep((info->time_to_die - total_time));
		info->philo_list[philo->id] = DEAD;
		philo->philo_status = DEAD;
		return (DEAD);
	}
	pthread_mutex_lock(&info->print_mutex);
	if (info->pls_print)
	{
		// printf("State of print sleeping fxn 2:%d:\n", info->pls_print);
		ft_print_info(philo, get_time_in_ms(), SLEEPING);
	}
	pthread_mutex_unlock(&info->print_mutex);
	ms_sleep(info->time_to_sleep);
	return (0);
}

int	thinking(t_info *info, t_philo *philo)
{
	if (info->philo_list[philo->id] == DEAD)// 50 philos will go // 1 check and wait in lock but philo 2 died and prints but 1 still in lock without knowing
		return (DEAD);
	pthread_mutex_lock(&info->print_mutex);//49 know someone died but 1 dont 
	if (info->pls_print)
	{
		// printf("State of print thinking fxn 1:%d:\n", info->pls_print);
		ft_print_info(philo, get_time_in_ms(), THINKING);
	}
	pthread_mutex_unlock(&info->print_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_info	*info;
	t_philo	philo;

	info = (t_info *)arg;
	philo.id = get_philo_position(info) - 1;
	philo.start_time = info->start_time;
	philo.last_eat_time = philo.start_time;
	philo.total_philos = info->total_philos;
	philo.philo_list = info->philo_list;
	philo.pls_print = info->pls_print;
	if (philo.id == 0 && info->total_philos == 1)
	{
		pthread_mutex_lock(&info->chop_sticks[philo.id]);
		printf("%lu Philo %d has taken fork %d, the RIGHT fork\n", get_time_in_ms() - philo.last_eat_time, philo.id + 1, philo.id);
		pthread_mutex_unlock(&info->chop_sticks[philo.id]);
		ms_sleep(info->time_to_die);
		kill_all_philos(info);
		return (NULL);
	}
	while (true)
	{
		if (eating(info, &philo) == DEAD)
			break ;
		if (sleeping(info, &philo) == DEAD)
			break ;
		if (thinking(info, &philo) == DEAD)
			break ;
	}
	return (NULL);
}
