/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:57:52 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/14 13:53:37 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (6);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (INVALID_ARGS);
		i++;
	}
	return (0);
}

int	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (6);
	while (i < argc)
	{
		if (check_args(argv[i]))
			return (INVALID_ARGS);
		i++;
	}
	return (0);
}

int	invalid_args(int argc, char **argv)
{
	int	i;

	i = parse_args(argc, argv);
	if (i)
		ft_perror(INVALID_ARGS);
	return (i);
}

int	invalid_philo(char **argv)
{
	if (ft_atoi(argv[1]) > 200
		|| ft_atoi(argv[1]) == 0)
	{
		ft_perror(INVALID_PHILO);
		return (INVALID_PHILO);
	}
	return (0);
}

int	invalid_time_args(char **argv)
{
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
	{
		ft_perror(INVALID_TIME);
		return (INVALID_TIME);
	}
	return (0);
}
