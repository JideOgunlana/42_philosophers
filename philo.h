/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:07:39 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/06 17:59:13 by bogunlan         ###   ########.fr       */
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
# include "colours.h"

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
	pthread_mutex_t	mtx_end;
	pthread_mutex_t	*chop_sticks;
	int				*chop_stick_status;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	size_t				start;
	int				philo_dies;
}				t_info;

typedef struct s_philos
{
	t_info		*info;
	int			position;
	int			l_chop_stick;
	int			r_chop_stick;
	int			num_eat;
	size_t		last_eat_time;
	enum	philo_state	state;
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

void	philo_eat(t_philos *);
void	philo_sleep(t_philos *);
void	philo_think(t_philos *);
void	print_philo_status(t_philos *philo, char *status);

/*
===============================================
                 Fxns for time                 
===============================================
 */
size_t	get_useconds(void);
void	ft_usleep(useconds_t time);


void	check_philos_death(t_philos *philo, t_info *info);
void	clean_up(pthread_t *threads, t_info *info, t_philos *philos);


#endif