/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:18:37 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 04:40:43 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 11L
int	prep_party(int argc, char **argv, t_data *data)
{
	int	err_id;

	memset(data, '\0', sizeof(t_data));
	err_id = parse_args(argc, argv, &(data->pr));
	if (err_id != OK)
		return (err_id);
	err_id = init(data);
	if (err_id != OK)
		return (err_id);
	register_philos(data);
	return (err_id);
}

// 23L
void	register_philos(t_data *data)
{
	size_t			i;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

	i = 0;
	while (i < (size_t)data->pr.num_philos)
	{
		data->philos[i].dine = &data->dine[i];
		data->philos[i].id = i + 1;
		data->philos[i].pr = &data->pr;
		fork_r = &data->forks[i];
		if (i + 1 == (size_t)data->pr.num_philos)
			fork_l = &data->forks[0];
		else
			fork_l = &data->forks[i + 1];
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].first_fork = fork_r;
			data->philos[i].second_fork = fork_l;
		}
		else if (data->philos[i].id % 2 == 1)
		{
			data->philos[i].first_fork = fork_l;
			data->philos[i].second_fork = fork_r;
		}
		i++;
	}
}

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

	// while (1)
// 24L
int	monitor_party(t_data *data)
{
	size_t		i;
	long long	full_bellies;

	i = 0;
	full_bellies = 0;
	while (i < (size_t)data->pr.num_philos)
	{
		pthread_mutex_lock(data->philos[i].dine);
		if (get_current_time(NULL) - data->philos[i].last_eat_time > (t_time)data->pr.time_to_die)
		{
			print_msg(&data->philos[i], ACT_DEAD);
			data->pr.the_end_status = true;
			pthread_mutex_unlock(&data->pr.coffin_lock);
			pthread_mutex_unlock(data->philos[i].dine);
			return (E_DEAD);
		}
		if (data->philos[i].eat_times == data->pr.min_times_to_eat)
			full_bellies++;
		pthread_mutex_unlock(data->philos[i].dine);
		i++;
	}
	if (full_bellies == data->pr.num_philos)
	{
		printf("FULL!!!!!!!!!!");
		return (FULL);
	}
	return (OK);
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
