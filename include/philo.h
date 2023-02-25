/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:07:39 by bogunlan          #+#    #+#             */
/*   Updated: 2023/02/24 15:16:01 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include "colours.h"
# include "error_messages.h"

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define LEFT 4
# define RIGHT 5
# define DEAD 6
# define INVALID_ARGS 7
# define INVALID_PHILO 8
# define INVALID_TIME 9

typedef enum e_errors
{
	no_errors,
	arg_error,
	malloc_error,
	mutex_error,
	thread_error,
}			t_errors;

typedef struct s_monitor
{
	int		total_philos;
	int		eat_limit;
	int		end_simulation;
	int		dead_philo_id;
	size_t	end_time;
}				t_monitor;

typedef struct s_philo
{
	int		id;
	int		philo_status;
	int		total_philos;
	int		*philo_list;
	int		pls_print;
	size_t	start_time;
	size_t	last_eat_time;
}				t_philo;

typedef struct s_info
{
	int				total_philos;
	int				count_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				eat_limit;
	int				eat_count;
	int				*chop_stick_status;
	int				*philo_list;
	int				pls_print;
	size_t			start_time;
	pthread_mutex_t	*chop_sticks;
	pthread_mutex_t	read_shared_var;
	pthread_mutex_t	print_mutex;
	pthread_t		*philos;
	int				i;
}				t_info;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);

int		check_args(char *str);
int		parse_args(int argc, char **argv);
int		invalid_args(int argc, char **argv);
int		invalid_philo(char **argv);
int		invalid_time_args(int argc, char **argv);
void	ft_perror(int err_num);

size_t	get_time_in_ms(void);

void	*monitor(void	*philo_info);
void	kill_all_philos(t_info *info);
int		is_any_philo_dead(t_info *info, t_monitor *monitor);
int		at_eat_limit(t_info *info, t_monitor *monitor);

int		init_info(int argc, char **argv, t_info *info);
int		ft_create_thread(t_info *info);

int		get_philo_position(t_info *info);
void	ms_sleep(size_t time);

void	*routine(void *philo_info);
int		thinking(t_info *info, t_philo *philo);
int		sleeping(t_info *info, t_philo *philo);
int		eating(t_info *info, t_philo *philo);

void	ft_print_info(t_philo *philo, size_t present_time, int c);
void	clean_up(t_info *info);

#endif