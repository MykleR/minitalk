/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:15:57 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/14 00:35:51 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

size_t	ft_strlen(const char *str)
{
	const char	*start;

	if (__builtin_expect(!str, 0))
		return (0);
	start = str;
	while (*str)
		str++;
	return (str - start);
}

bool	ft_safe_atopid(const char *str, pid_t	*out)
{
	uint64_t	res;

	if (__builtin_expect(!str || !out, 0))
		return (false);
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r')
		str++;
	str += (*str == '+');
	if (!(*str))
		return (false);
	while (*str)
	{
		res = (res << 1) + (res << 3) + *str - '0';
		if (*str < '0' || *str++ > '9' || res > INT32_MAX)
			return (false);
	}
	*out = res;
	return (true);
}
