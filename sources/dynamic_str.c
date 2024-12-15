/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:20:27 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/15 20:08:49 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

bool	dynamic_str_create(t_dynamic_str *str)
{
	if (__builtin_expect(!str, 0))
		return (false);
	str->cap = STR_INIT_CAP;
	str->len = 0;
	str->data = dc_malloc(sizeof(char) * STR_INIT_CAP);
	return (str->data != NULL);
}

void	dynamic_str_destroy(t_dynamic_str *str)
{
	if (__builtin_expect(!str, 0))
		return ;
	dc_free(str->data);
	str->data = 0;
	str->len = 0;
	str->cap = 0;
}

void	dynamic_str_add(t_dynamic_str *str, int c)
{
	if (__builtin_expect(!str, 0))
		return ;
	if (__builtin_expect(str->len >= str->cap, 0))
	{
		if ((str->cap << 1) >> 1 != str->cap)
			exit(1);
		str->data = dc_realloc(str->data, str->cap * sizeof(char),
				(str->cap << 1) * sizeof(char));
		str->cap <<= 1;
	}
	str->data[str->len++] = c;
}

void	dynamic_str_print(t_dynamic_str *str)
{
	write(1, str->data, str->len);
}
