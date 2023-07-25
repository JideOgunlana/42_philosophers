/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:52:55 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/27 06:22:38 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

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
	info->chop_stick_status = malloc(sizeof(int) * info->total_philos);
	if (!info->chop_stick_status || !info->philo_list)
		return (malloc_error);
	info->count_philos = 0;
	info->eat_count = 0;
	info->pls_print = 1;
	info->start_time = get_time_in_ms();
	return (no_errors);
}

int	ft_create_thread(t_info *info)
{
	int	i;

	info->philos = (pthread_t *)malloc(sizeof(pthread_t) * info->total_philos);
	if (!info->philos)
		return (malloc_error);
	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_create(&info->philos[i], NULL, routine, info))
			return (thread_error);
		i += 1;
	}
	return (no_errors);
}

int	init_mutexes(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(info->read_shared_var), NULL))
		return (mutex_error);
	if (pthread_mutex_init(&(info->print_mutex), NULL))
		return (mutex_error);
	info->chop_sticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	info->total_philos);
	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_mutex_init(&(info->chop_sticks[i]), NULL))
			return (mutex_error);
		i++;
	}
	return (no_errors);
}

int	main(int argc, char **argv)
{
	t_info		info;

	if (invalid_args(argc, argv))
		return (arg_error);
	if (invalid_philo(argv) || invalid_time_args(argc, argv))
		return (arg_error);
	if (init_info(argc, argv, &info) != no_errors)
		return (malloc_error);
	if (init_mutexes(&info) != no_errors)
		return (mutex_error);
	if (ft_create_thread(&info) != no_errors)
		return (thread_error);
	monitor(&info);
	info.i = -1;
	while (++info.i < info.total_philos)
		pthread_join(info.philos[info.i], NULL);
	clean_up(&info);
	return (0);
}
