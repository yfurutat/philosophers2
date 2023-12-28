/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_get_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:55:07 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 02:39:09 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 9L
t_time	get_current_time(int *err_ptr)
{
	struct timeval 	tp;
	int				err_id;

	err_id = gettimeofday(&tp, NULL);
	if (err_ptr)
		*err_ptr = err_id;
	if (err_id != OK)
		return (UINTMAX_MAX);
	return((tp.tv_usec / 1000) + (tp.tv_sec * 1000));
}

// 13L
int	print_msg(t_ph *philo, const char *action)
{
	t_time	time_stamp;

	pthread_mutex_lock(&philo->pr->coffin_lock);
	time_stamp = get_current_time(NULL) - (philo->pr->start_time);
	if (philo->pr->the_end_status == true)
	{
		pthread_mutex_unlock(&philo->pr->coffin_lock);
		return (E_DEAD);
	}
	printf("%ju %lld %s\n", time_stamp, philo->id, action);
	if (action[0] != 'd')
		pthread_mutex_unlock(&philo->pr->coffin_lock);
	return (OK);
}
