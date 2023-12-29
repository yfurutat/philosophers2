/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe_party.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfurutat <yfurutat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:18:37 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 20:46:27 by yfurutat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitor_dine(t_data *data);


// 8L
int	observe_party(t_data *data)
{
	long long	full_bellies;

	full_bellies = monitor_dine(data);
	if (full_bellies == -1)
		return (E_DEAD);
	else if (full_bellies == data->pr.num_philos)
		return (FULL);
	return (OK);
}
	// while (1)
	// size_t		i;
	// i = 0;
	// {
	// 	printf("FULL!!!!!!!!!!");
	// 	return (FULL);
	// }
	// {
	// 	printf("DEAD!!!!!!!!!!");
	// 	return (E_DEAD);
	// }

	// long long	full_bellies;
	// full_bellies = 0;
// 23L
static int	monitor_dine(t_data *data)
{
	size_t		i;
	long long	cnt;

	i = 0;
	cnt = 0;
	while (i < (size_t)data->pr.num_philos)
	{
		pthread_mutex_lock(data->philos[i].dine);
		if (get_current_time(NULL) - data->philos[i].last_eat_time \
			> (t_time)data->pr.time_to_die)
		{
			print_msg(&data->philos[i], ACT_DEAD);
			printf("LAST EAT: %ju\n", data->philos[i].last_eat_time \
				- data->pr.start_time);
			pthread_mutex_unlock(data->philos[i].dine);
			return (-1);
		}
		if (data->philos[i].eat_times == data->pr.min_times_to_eat)
			cnt++;
		pthread_mutex_unlock(data->philos[i].dine);
		i++;
	}
	return (cnt);
}

// 12L
int	join_the_line(pthread_t *threads, size_t num)
{
	size_t	i;
	int		err_id;

	i = 0;
	while (i < num)
	{
		err_id = pthread_join(threads[i], NULL);
		if (err_id != OK)
			break ;
		i++;
	}
	return (err_id);
}
