/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:23:15 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/21 09:10:58 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	clean_up(t_info *info)
{
	int	i;

	i = info->total_philos - 1;
	while (i >= 0)
	{
		pthread_mutex_destroy(&(info->chop_sticks[i]));
		i--;
	}
	pthread_mutex_destroy(&(info->read_shared_var));
	free(info->philo_list);
	free(info->chop_stick_status);
	free(info->chop_sticks);
}
