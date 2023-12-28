/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efmacm23 <efmacm23@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:46:08 by efmacm23          #+#    #+#             */
/*   Updated: 2023/12/28 22:16:53 by efmacm23         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(int chr)
{
	return ((chr >= '\t' && chr <= '\r') || chr == ' ');
}

int	ft_isdigit(int chr)
{
	return (chr >= '0' && chr <= '9');
}

static bool	_ft_isdigit_str(char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	if ((*str == '+' || *str == '-') && ft_isdigit(*(str + 1)))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ft_aredigit_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return (E_EMPTY);
	i = 1;
	while (strs[i])
	{
		if (_ft_isdigit_str(strs[i]) == false)
			return (E_NONDIGIT);
		i++;
	}
	return (OK);
}
	// size_t	len;
	// len = 0;
		// len = ft_strlen(argv[i]);
		// if (!len || len > 10)
		// 	return (INVALID_LEN);
