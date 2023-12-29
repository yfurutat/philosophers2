/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:18:37 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 06:10:21 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 25L
int	start_party(t_data *data)
{
	size_t	i;
	int		err_id;

	i = 0;
	err_id = OK;
	data->pr.start_time = get_current_time(&err_id) + 1000;
	if (err_id != OK)
		return (E_GETTIME);
	pthread_mutex_lock(&data->pr.coffin_lock);
	while (i < (size_t)data->pr.num_philos)
	{
		data->philos[i].last_eat_time = data->pr.start_time;
		if (pthread_create(&data->threads[i], NULL, philo_act, \
			&data->philos[i]) != OK)
		{
			data->pr.the_end_status = true;
			pthread_mutex_unlock(&data->pr.coffin_lock);
			join_the_line(data->threads, i);
			return (E_PTHREAD_CREATE);
		}
		i++;
	}
	pthread_mutex_unlock(&data->pr.coffin_lock);
	sleep_until(data->pr.start_time);
	return (OK);
}
