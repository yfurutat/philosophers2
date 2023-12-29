/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfurutat <yfurutat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:54:09 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 18:21:26 by yfurutat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
	HEADERS
*/

// # include "philo_utils.h"
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <stdint.h>
# include <unistd.h> // write, usleep
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <sys/time.h> // gettimeofday
# include <pthread.h> 
// pthread_create, pthread_detach, pthread_join, 
// pthread_mutex_init, pthread_mutex_destroy, 
// pthread_mutex_lock, pthread_mutex_unlock

/*
	MACROS
*/

# define POSITIVE (1)
# define NEGATIVE (-1)
# define ACT_FORK "has taken a fork"
# define ACT_EAT "is eating"
# define ACT_SLEEP "is sleeping"
# define ACT_THINK "is thinking"
# define ACT_DEAD "died"
# define ANSI_BOLD_RED "\x1b[1;31m"
# define ANSI_RESET "\x1b[0m"

/*
	TYPEDEF
*/

typedef uintmax_t	t_time;

typedef struct s_param {
	long long		num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		min_times_to_eat;
	bool			the_end_status;
	pthread_mutex_t	coffin_lock;
	t_time			start_time;
}	t_param;
	// bool			thread_err;
	// pthread_mutex_t	for_thread_err;

typedef struct s_philo {
	long long		id;
	long long		eat_times;
	t_time			last_eat_time;
	pthread_mutex_t	*dine;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_param			*pr;
}	t_ph;

typedef struct s_data {
	t_ph			*philos;
	t_param			pr;
	pthread_t		*threads;
	pthread_mutex_t	*dine;
	pthread_mutex_t	*forks;
}	t_data;

typedef enum e_error {
	OK = 0,
	FULL,
	E_EMPTY,
	E_INVALID_ARGC,
	E_NONDIGIT,
	E_INVALID_LEN,
	E_INVALID_VALUE,
	E_ALLOC,
	E_INITF,
	E_GETTIME,
	E_PTHREAD_CREATE,
	E_DEAD,
	E_DESTROY,
	E_PRINT,
}	t_err;

// typedef enum e_atol {
// 	FLOW = 1,
// }	t_atol;

/*
	FUNCTIONS
*/

int			prep_party(int argc, char **argv, t_data *data);
int			start_party(t_data *data);
int			observe_party(t_data *data);
int			join_the_line(pthread_t *threads, size_t num);

int			parse_args(int argc, char **argv, t_param *pr); // complemental: 2
int			init(t_data *data); // complemental: 1
void		*philo_act(void *param); // complemental: 4

// DESTROY
int			destroy_mutex_array(pthread_mutex_t *ptr, size_t num);
int			destroy_data(t_data *data, t_err code);

int			print_msg(t_ph *philo, const char *action);
t_time		get_current_time(int *err_ptr);

// UTILS
int			wait_until_start_time(t_ph *philo);
int			sleep_until(t_time finish_time);
int			ft_millisleep(t_time sleep_time);
int			ft_isspace(int chr);
int			ft_isdigit(int chr);
int			ft_aredigit_strs(char **strs);
long long	ft_atoll(const char *str);
ssize_t		ft_strlen(const char *str);
ssize_t		ft_putstr_fd(const char *str, int fd);
// bool		ft_isdigit_str(char *str);

#endif