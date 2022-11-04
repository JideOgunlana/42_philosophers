/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:07:39 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/01 20:28:34 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define FREE 0
# define LOCK 1
# include <stdio.h>

enum philo_state
{
	SLEEPING = 1,
	THINKING,
	EATING
};

typedef struct s_info
{
	pthread_mutex_t	*chop_sticks;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	int				*chop_stick_status;
}				t_info;

typedef struct s_philos
{
	t_info	*info;
	int		position;
	int		l_chop_stick;
	int		r_chop_stick;
	enum philo_state	state;
}				t_philos;

t_philos	*all(void);

/*
===============================================
   utility fxns used by philosopher program    
===============================================
 */
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

/*
===============================================
               Input Parsing fxns              
===============================================
 */

/**
 * @brief parses the input arguments passed to the philosopher program
 * 
 * @param argc count of args passed
 * @param argv array of strings passed to philosopher program
 * @return int
 */
int		parse_args(int argc, char **argv);

/**
 * @brief checks for values that is not a valid arg
 *
 * @param str array of strings passed to philosopher program
 * @return int
 */
int		check_args(char *str);

/*
===============================================
         Fxns for philosopher routines         
===============================================
 */

void	philo_eat(int);
void	philo_sleep(t_philos *);
void	philo_think(t_philos *);

#endif