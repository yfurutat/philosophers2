/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:47:24 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 06:13:01 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_philo_pick_up_fork(t_ph *philo);
static int	_philo_eat(t_ph *philo);
static int	_philo_sleep(t_ph *philo);
static int	_philo_think(t_ph *philo);

int	wait_until_start_time(t_ph *philo)
{
	pthread_mutex_lock(&philo->pr->coffin_lock);
	if (philo->pr->the_end_status == true)
	{
		pthread_mutex_unlock(&philo->pr->coffin_lock);
		return (E_DEAD);
	}
	pthread_mutex_unlock(&philo->pr->coffin_lock);
	sleep_until(philo->pr->start_time);
	return (OK);
}

// 13L
void *philo_act(void *param)
{
	t_ph *philo;

	philo = (t_ph *)param;
	if (wait_until_start_time(philo) != OK)
		return (NULL);
	if (philo->pr->min_times_to_eat == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_millisleep(philo->pr->time_to_eat / 2);
	while (1)
	{
		if (_philo_eat(philo))
			break ;
		if (_philo_sleep(philo))
			break ;
		if (_philo_think(philo))
			break ;
	}
	return (NULL);
}

// 23L
static int	_philo_pick_up_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (print_msg(philo, ACT_FORK) == E_DEAD || philo->pr->num_philos == 1)
	{
		pthread_mutex_unlock(philo->first_fork);
		return (E_DEAD);
	}
	pthread_mutex_lock(philo->second_fork);
	if (print_msg(philo, ACT_FORK) == E_DEAD)
	{
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_unlock(philo->first_fork);
		return (E_DEAD);
	}
	return (OK);
}

// 19L
static int	_philo_eat(t_ph *philo)
{
	if (_philo_pick_up_fork(philo) != OK)
		return (E_DEAD);
	pthread_mutex_lock(philo->dine);
	if (print_msg(philo, ACT_EAT) == E_DEAD)
	{
		pthread_mutex_unlock(philo->dine);
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_unlock(philo->first_fork);
		return (E_DEAD);
	}
	// pthread_mutex_lock(philo->dine);
	philo->last_eat_time = get_current_time(NULL);
	philo->eat_times++;
	pthread_mutex_unlock(philo->dine);
	if (ft_millisleep(philo->pr->time_to_eat))
		return (E_GETTIME);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
	if (philo->eat_times == philo->pr->min_times_to_eat)
		return (FULL);
	return (OK);
}

// 5L
static int	_philo_sleep(t_ph *philo)
{
	if (print_msg(philo, ACT_SLEEP) == E_DEAD)
		return (E_DEAD);
	if (ft_millisleep(philo->pr->time_to_sleep))
		return (E_GETTIME);
	return (OK);
}

// 3L
static int	_philo_think(t_ph *philo)
{
	if (print_msg(philo, ACT_THINK) == E_DEAD)
		return (E_DEAD);
	return (OK);
}
