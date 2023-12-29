/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfurutat <yfurutat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:52:53 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/29 20:08:31 by yfurutat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (action[0] == 'd')
		philo->pr->the_end_status = true;
	pthread_mutex_unlock(&philo->pr->coffin_lock);
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
