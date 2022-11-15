/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:52:55 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/15 19:35:54 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_mutexes_init(pthread_mutex_t **mutexes, size_t total_philos)
{
	*mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
				* total_philos);
	if (!(*mutexes))
		return (1);
	while (total_philos > 0)
	{
		if (pthread_mutex_init(&((*mutexes)[total_philos]), NULL))
			return (-1);
		total_philos--;
	}
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->total_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_limit = ft_atoi(argv[5]);
	else
		info->eat_limit = -1;
	info->philo_list = malloc(sizeof(int) * info->total_philos);
	info->using_chop_sticks = malloc(sizeof(int) * info->total_philos);
	if (!info->using_chop_sticks || !info->philo_list)
		return (1);
	if (ft_mutexes_init(&(info->philo_dead_mutex), info->total_philos) == -1)
		return (1);
	if (pthread_mutex_init(&(info->mutex), 0))
		return (1);
	if (ft_mutexes_init(&(info->chop_sticks), info->total_philos) == -1)
		return (1);
	info->count_philos = 0;
	info->eat_count = 0;
	info->start_time = get_time();
	// memset(info->using_chop_sticks, 0, sizeof(int) * info->total_philos);
	// memset(info->philo_list, 0, sizeof(int) * info->total_philos);
	return (0);
}

int	ft_create_thread(t_info *info, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_create(&philos[i], NULL, routine, info))
			return (-1);
		usleep(100);
		i += 1;
	}
	return (0);
}

pthread_t	*ft_malloc_philos(t_info *info)
{
	pthread_t	*philos;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * info->total_philos);
	if (!philos)
		return (NULL);
	return (philos);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	pthread_t	*philos;
	pthread_t	death_monitor;

	if (invalid_args(argc, argv))
		return (0);
	if (invalid_philo(argv) || invalid_time_args(argv))
		return (0);
	if (init_info(argc, argv, &info))
		return (0);
	philos = ft_malloc_philos(&info);
	if (!philos)
		return (0);
	if (ft_create_thread(&info, philos) == -1)
		return (0);
	if (pthread_create(&death_monitor, NULL, monitor, &info))
		return (0);
	info.i = -1;
	while (++info.i < info.total_philos)
		pthread_join(philos[info.i], NULL);
	pthread_join(death_monitor, NULL);
	clean_up(&info, &philos);
	return (0);
}
