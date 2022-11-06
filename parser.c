/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:57:52 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/06 19:01:11 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		printf("%sEmpty string passed%s\n", YELLOW, END);
		return (1);
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) || ft_atoi(str) == 0)
		{
            printf("%sPassed '0'\n\t- OR -%s\n", YELLOW, END);
			printf("%sPassed args Contain non digit character%s\n", YELLOW, END);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("%sError%s\n", RED, END);
		printf("%sMany or little args passed%s\n", YELLOW, RED);
		return (1);
	}
	while (i < argc)
	{
		if (check_args(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
