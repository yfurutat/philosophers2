/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:52:53 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 03:59:48 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_until(t_time finish_time)
{
	int	err_id;

	while (get_current_time(&err_id) < finish_time)
	{
		if (err_id != OK)
			return (E_GETTIME);
		usleep(50);
	}
	return (OK);
}

int	ft_millisleep(t_time sleep_time)
{
	t_time	start_time;
	int		err_id;

	start_time = get_current_time(&err_id);
	if (err_id != OK)
		return (err_id);
	while (get_current_time(&err_id) - start_time < sleep_time)
	{
		if (err_id != OK)
			return (E_GETTIME);
		usleep(50);
	}
	return (OK);
}

ssize_t	ft_putstr_fd(const char *str, int fd)
{
	ssize_t	ret;

	ret = write(fd, str, ft_strlen(str));
	return (ret);
}

ssize_t	ft_strlen(const char *str)
{
	ssize_t	len;

	if (str == NULL)
		return (-1);
	len = 0;
	while (str[len])
	{
		len++;
		if (len == SSIZE_MAX)
			return (-1);
	}
	return (len);
}
	// while (ft_isspace(*str))
	// 	str++;

// bool    is_num(const char *str)
// {
//     if (*str == '\0')
//         return (false);
//     if ((*str == '+' || *str == '-') && ft_isdigit(*(str + 1)))
//         str++;
//     while (*str != '\0' && ft_isdigit(*str))
//         str++;
//     if (*str != '\0')
//         return (false);
//     return (true);
// }
