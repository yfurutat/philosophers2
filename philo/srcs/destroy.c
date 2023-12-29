/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfurutat <yfurutat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:45:29 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 20:06:44 by yfurutat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_error(t_err code);
// static void	print_error(t_err code);
// static int	print_error(int err_id);
// static char	*what_error(int err_id);

	// errno = OK;
// 17L
int	destroy_data(t_data *data, t_err code)
{
	int		ret;

	ret = print_error(code);
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
		ret = print_error(E_DESTROY);
	return (ret);
}

// 16L
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

// 24L
// static void	print_error(t_err code)
static int	print_error(t_err code)
{
	const char	*error_messages[] = {\
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

	if (code != OK && code != FULL)
	{
		if (ft_putstr_fd(ANSI_BOLD_RED, STDERR_FILENO) < 0)
			return (print_error(E_PRINT));
		if (ft_putstr_fd(error_messages[code], STDERR_FILENO) < 0)
			return (print_error(E_PRINT));
		if (ft_putstr_fd(ANSI_RESET, STDERR_FILENO) < 0)
			return (print_error(E_PRINT));
	}
	return (OK);
}
	// ft_putstr_fd(error_messages[code], STDERR_FILENO);

// // 18L
// static int	print_error(int err_id)
// {
// 	int			ret;
// 	const char	*str = what_error(err_id);

// 	if (err_id == OK || err_id == FULL)
// 		return (OK);
// 	ret = ft_putstr_fd(ANSI_BOLD_RED, STDERR_FILENO);
// 	if (ret < 0)
// 		return (print_error(err_id));
// 	ret = ft_putstr_fd("ERROR: ", STDERR_FILENO);
// 	if (ret < 0)
// 		return (print_error(err_id));
// 	ret = ft_putstr_fd(str, STDERR_FILENO);
// 	if (ret < 0)
// 		return (print_error(err_id));
// 	ret = ft_putstr_fd(ANSI_RESET, STDERR_FILENO);
// 	if (ret < 0)
// 		return (print_error(err_id));
// 	return (OK);
// }

// // 25L
// static char	*what_error(int err_id)
// {
// 	if (err_id == E_EMPTY)
// 		return ("EMPTY PARAMETER\n");
// 	else if (err_id == E_INVALID_ARGC)
// 		return ("INVALID_ARGC\n");
// 	else if (err_id == E_NONDIGIT)
// 		return ("NON-DIGIT ARGV\n");
// 	else if (err_id == E_INVALID_LEN)
// 		return ("INVALID LENGTH\n");
// 	else if (err_id == E_INVALID_VALUE)
// 		return ("INVALID VALUE\n");
// 	else if (err_id == E_ALLOC)
// 		return ("ALLOCATION FAILED\n");
// 	else if (err_id == E_INITF)
// 		return ("INITIALIZATION FAILED\n");
// 	else if (err_id == E_GETTIME)
// 		return ("GETTIME FAILED\n");
// 	else if (err_id == E_PTHREAD_CREATE)
// 		return ("PTHREAD CREATION FAILED\n");
// 	else if (err_id == E_DEAD)
// 		return ("A PHILOSOPHER HAS DIED\n");
// 	else if (err_id == E_DESTROY)
// 		return ("DESTRUCTION FAILED\n");
// 	else if (err_id == E_PRINT)
// 		return ("PRINT FAILED\n");
// 	return ("NO ERROR...ACTUALLY\n");
// }
