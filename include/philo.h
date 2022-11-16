/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:07:39 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/16 18:58:34 by bogunlan         ###   ########.fr       */
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
# include "colours.h"
# include "error_messages.h"

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4
# define CHOP_STICK_TAKEN 5
# define INVALID_ARGS 6
# define INVALID_PHILO 7
# define INVALID_TIME 8
# include <stdio.h>

typedef struct s_monitor
{
	int		total_philos;
	int		eat_limit;
	int		end_eat;
	int		end_simulation;
	int		dead_philo_id;
	size_t	end_time;
}				t_monitor;

typedef struct s_philo
{
	int		id;
	int		l_chop_stick;
	int		r_chop_stick;
	int		lcs;
	int		rcs;
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
	int				*using_chop_sticks;
	int				*philo_list;
	size_t			start_time;
	pthread_mutex_t	*philo_dead_mutex;
	pthread_mutex_t	*chop_sticks;
	pthread_mutex_t	mutex;
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

size_t	get_time(void);
void	ft_sleep(size_t sleep_time);

void	*monitor(void	*philo_info);
void	ft_kill_all_philos(t_info *info);
int		ft_is_any_philo_dead(t_info *info, t_monitor *monitor);
int		ft_at_eat_limit(t_info *info, t_monitor *monitor);

int		init_info(int argc, char **argv, t_info *info);
int		ft_mutexes_init(pthread_mutex_t **mutexes, size_t total_philos);
int		ft_create_thread(t_info *info, pthread_t *philos);

size_t	ft_get_philo_position(t_info *info);
void	ft_get_chop_stick_num(t_philo *philo, t_info *info);
void	ft_usleep(size_t time);

void	*routine(void *philo_info);
int		ft_thinking(t_info *info, t_philo *philo);
int		ft_sleeping(t_info *info, t_philo *philo);
int		ft_eating(t_info *info, t_philo *philo);

int		ft_philo_died(t_info *info, t_philo *philo);
int		ft_is_philo_dead(t_info *info, int philo_id);

int		ft_lock_chop_sticks(t_info *info, t_philo *philo, char c);
void	ft_unlock_chop_sticks(t_info *info, t_philo *philo, char c);
int		ft_is_chop_stick_used(t_info *info, t_philo *philo, char c);

void	ft_print_info(t_philo *info, size_t present_time, int c);
void	clean_up(t_info *info, pthread_t **philos);

#endif