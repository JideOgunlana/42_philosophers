/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:22 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/21 19:45:17 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ms_sleep(size_t time)
{
	size_t	time_in_ms;

	time_in_ms = get_time_in_ms();
	while (true)
	{
		if (get_time_in_ms() - time_in_ms >= time)
			break ;
		usleep(40);
	}
}
