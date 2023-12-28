/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:45:29 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 03:55:22 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    print_error(t_err code);

	// errno = OK;
// 11L
int	destroy_data(t_data *data, t_err code)
{
	int		ret;

	print_error(code);
	ret = OK;
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->threads)
			free(data->threads);
		if (data->forks)
			ret = destroy_mutex_array(data->forks, (size_t)data->pr.num_philos);
		if (data->dine)
			ret = destroy_mutex_array(data->dine, (size_t)data->pr.num_philos);
	}
	if (ret != OK)
		print_error(E_DESTROY);
	return (ret);
}

// 11L
int	destroy_mutex_array(pthread_mutex_t *ptr, size_t num)
{
	size_t	i;
	int		err_id;

	err_id = OK;
	if (ptr == NULL)
		return (E_EMPTY);
	i = 0;
	while (i < num)
	{
		err_id = pthread_mutex_destroy(&ptr[i]);
		if (err_id != OK)
			break ;
		i++;
	}
	free(ptr);
	return (err_id);
}

static void	print_error(t_err code)
{
	ssize_t	ret;	
    const char    *error_messages[] = {\
        [E_EMPTY] = "ERROR: EMPTY PARAMETER\n", \
		[E_INVALID_ARGC] = "ERROR: INVALID_ARGC\n", \
		[E_NONDIGIT] = "ERROR: NON-DIGIT ARGV\n", \
		[E_INVALID_LEN] = "ERROR: INVALID LENGTH\n", \
		[E_INVALID_VALUE] = "ERROR: INVALID VALUE\n", \
		[E_ALLOC] = "ERROR: ALLOCATION FAILED\n", \
		[E_INITF] = "ERROR: INITIALIZATION FAILED\n", \
		[E_GETTIME] = "ERROR: GETTIME FAILED\n", \
		[E_PTHREAD_CREATE] = "ERROR: PTHREAD CREATION FAILED\n", \
		[E_DEAD] = "ERROR: A PHILOSOPHER DIED\n", \
		[E_DESTROY] = "ERROR: DESTRUCTION FAILED\n", \
		[E_PRINT] = "ERROR: PRINT FAILED\n"};

    ret = ft_putstr_fd(ANSI_BOLD_RED, STDERR_FILENO);
	if (ret < 0)
		print_error(E_PRINT);
    ret = ft_putstr_fd(error_messages[code], STDERR_FILENO);
	if (ret < 0)
		print_error(E_PRINT);
    ret = ft_putstr_fd(ANSI_RESET, STDERR_FILENO);
	if (ret < 0)
		print_error(E_PRINT);
}
	// char	err_msg[10];
	// 	err_msg = 
// int	print_err_msg(int err_id)
// {
// 	int	ret;

// 	ft_putstr_fd(ANSI_BOLD_RED);
// 	if (err_id == E_EMPTY)
// 		ret = printf("ERROR: EMPTY PARAMETER\n");
// 	if (err_id == E_INVALID_ARGC)
// 		ret = printf("ERROR: INVALID_ARGC\n");
// 	if (err_id == E_NONDIGIT)
// 		ret = printf("ERROR: NON-DIGIT ARGV\n");
// 	if (err_id == E_INVALID_LEN)
// 		ret = printf("ERROR: INVALID LENGTH\n");
// 	if (err_id == E_INVALID_VALUE)
// 		ret = printf("ERROR: INVALID VALUE\n");
// 	if (err_id == E_ALLOC)
// 		ret = printf("ERROR: ALLOCATION FAILED\n");
// 	if (err_id == E_INITF)
// 		ret = printf("ERROR: INITIALIZATION FAILED\n");
// 	if (err_id == E_GETTIME)
// 		ret = printf("ERROR: GETTIME FAILED\n");
// 	if (err_id == E_PTHREAD_CREATE)
// 		ret = printf("ERROR: PTHREAD CREATION FAILED\n");
// 	if (err_id == E_DEAD)
// 		ret = printf("ERROR: A PHILOSOPHER DIED\n");
// 	if (err_id == E_DESTROY)
// 		ret = printf("ERROR: DESTRUCTION FAILED\n");
// 	if (ret < 0)
// 		ret = print_err_msg
// }
