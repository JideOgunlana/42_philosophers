/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:46:39 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/14 17:12:35 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	ft_perror(int err_num)
{
	if (err_num == INVALID_ARGS)
		printf("%s%s%s", RED, INVALID_ARGS_MESS, RESET);
	if (err_num == INVALID_PHILO)
		printf("%s%s%s", RED, INVALID_PHILO_MESS, RESET);
	if (err_num == INVALID_TIME)
		printf("%s%s%s", RED, INVALID_TIME_MESS, RESET);
	printf("%sUsage: %s%s%s%s%s", BLUE, RESET, ITALIC, YELLOW, USAGE, RESET);
}
