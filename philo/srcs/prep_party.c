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

static void	register_philos(t_data *data);
static void	prep_forks(t_data *data, size_t i);

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

	// pthread_mutex_t	*fork_r;
	// pthread_mutex_t	*fork_l;
// 23L
static void	register_philos(t_data *data)
{
	size_t			i;

	i = 0;
	while (i < (size_t)data->pr.num_philos)
	{
		data->philos[i].eat_times = 0;
		data->philos[i].dine = &data->dine[i];
		data->philos[i].id = i + 1;
		data->philos[i].pr = &data->pr;
		prep_forks(data, i);
		i++;
	}
}

static void	prep_forks(t_data *data, size_t i)
{
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

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
}
		// fork_r = &data->forks[i];
		// if (i + 1 == (size_t)data->pr.num_philos)
		// 	fork_l = &data->forks[0];
		// else
		// 	fork_l = &data->forks[i + 1];
		// if (data->philos[i].id % 2 == 0)
		// {
		// 	data->philos[i].first_fork = fork_r;
		// 	data->philos[i].second_fork = fork_l;
		// }
		// else if (data->philos[i].id % 2 == 1)
		// {
		// 	data->philos[i].first_fork = fork_l;
		// 	data->philos[i].second_fork = fork_r;
		// }
