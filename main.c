/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:52:55 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/06 19:13:26 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*all(void)
{
	static t_philos	all_philos;

	return (&all_philos);
}

void	*routine(void	*arg)
{
	// t_philos	*philos = all();
	// int index = *(int *) arg;
	while (true)
	{
		philo_eat((t_philos *)arg);
		philo_sleep((t_philos *) arg);
		philo_think((t_philos *)arg);
	}
	// printf("philos position: %d, philos count: %d\n",philos[index].position, philos[index].info->philos_count);
	// printf("philos position: %d, philos count: %d\n",philos[index].position, philos[index].info->philos_count);
	// printf("Index: %d\n", index);
	return (NULL);
}

int	start_philos(t_info *info, t_philos *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&threads[i], NULL, routine, &philos[i]))
		{
			printf("%sError(101)\nFailed to create philosopher threads%s\n", RED, END);
			return (101);
		}
		usleep(50);
		i++;
	}
	// i = 0;
	// while (i < info->philos_count)
	// {
	// 	if (pthread_join(threads[i], NULL))
	// 	{
	// 		printf("%sError(102)\nFailed to join threads%s\n", RED, END);
	// 		return (102);
	// 	}
	// 	i++;
	// }
	// free(threads);
	return (0);
}

int	init_chop_stick_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		if (pthread_mutex_init(&info->chop_sticks[i], NULL))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->philos_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_times_to_eat = ft_atoi(argv[5]);
	info->chop_sticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philos_count);
	info->chop_stick_status = (int *)malloc(sizeof(int) * info->philos_count);
	if (!info->chop_sticks || !info->chop_stick_status)
		return (1);
	memset(info->chop_stick_status, FREE, info->philos_count);
	if (init_chop_stick_mutex(info))
	{
		printf("%sMutex initialization error%s\n", RED, END);
		return (1);
	}
	info->start = get_useconds();
	// printf("Philosopher count: %d\n Time to die %d\n Time to eat: %d\n Time to sleep: %d\n Must eat time: %d\n", info->philos_count, info->time_to_die, info->time_to_eat, info->time_to_sleep, info->n_times_to_eat);
	return (0);
}

t_philos	*init_philo(t_info *info)
{
	int		i;
	t_philos *philos;

	philos = all();
	i = 0;
	while (i < info->philos_count)
	{
		philos[i].info = info;
		philos[i].position = i + 1;
		philos[i].r_chop_stick = i;
		philos[i].l_chop_stick = (i + 1) % info->philos_count;
		philos[i].state = SLEEPING;
		philos[i].last_eat_time = info->start;
		philos[i].num_eat = 0;
		i++;
	}
/* 	while (i < info->philos_count)
	{
		printf("**philos position: %d, philos count: %d**\n",philos[i].position, philos[i].info->philos_count);
		i++;
	} */
	return (philos);
}

int	main(int argc, char *argv[])
{
	t_philos	*philos;
	t_info		*info;
	pthread_t	*threads;

	// (void) philos;
	(void) threads;

	if (parse_args(argc, argv))
	{
		printf("%sUsage:%s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[OPTIONAL]number_of_times_each_philosopher_must_eat>\n", YELLOW, END);
		return (0);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Invalid arg, max is 200\n");
		return (0);
	}
	info = (t_info *)malloc(sizeof(t_info));
	// philos = (t_philos *)malloc(sizeof(t_philos) * info->philos_count);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * info->philos_count);
	if (!info || /* !philos || */ !threads)
		return (0);
	if (init_info(argc, argv, info))
	{
		printf("Info initialization failed\n");
		return (0);
	}
	philos = init_philo(info);
	start_philos(info, philos, threads);
	check_philos_death(philos, info);
	// printf("Philo: 1 -> L: %d, R: %d\n", philos[0].l_chop_stick, philos[0].r_chop_stick);
	// printf("Philo: 2 -> L: %d, R: %d\n", philos[1].l_chop_stick, philos[1].r_chop_stick);
	// clean_up(threads, info, philos);
	printf("|Checking philo death|\n");
	return (0);
}
