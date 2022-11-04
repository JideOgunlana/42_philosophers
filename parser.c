/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:57:52 by bogunlan          #+#    #+#             */
/*   Updated: 2022/10/31 17:12:08 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		printf("Empty string passed\n");
		return (1);
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) || ft_atoi(str) == 0)
		{
            printf("Passed '0' OR\n");
			printf("Passed args Contain non digit character\n");
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
		printf("Many or little args passed\n");
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
