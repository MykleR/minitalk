/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:14:32 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/14 00:35:42 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	char_to_bits(char c, int *bits)
{
	uint32_t	i;

	i = -1;
	while (++i < 8)
		bits[i] = (c << i) & (1 << 7);
}

bool	bits_to_string(const t_bits_str *bits, char **str_out)
{
	uint32_t	bit_count;
	char		c;

	if (__builtin_expect(!bits || !str_out, 0))
		return (false);
	c = 0;
	bit_count = -1;
	*str_out = malloc(sizeof(char) * (bits->len / 8) + 1);
	if (!(*str_out))
		return (false);
	while (++bit_count < bits->len)
	{
		c = (c << 1) | (bits->data[bit_count] != 0);
		if (bit_count % 8 == 7)
		{
			(*str_out)[((bit_count + 1) / 8) - 1] = (char)c;
			c = 0;
		}
	}
	(*str_out)[bit_count / 8] = 0;
	return (true);
}

bool	string_to_bits(const char *str, t_bits_str *bits_out)
{
	int	byte_index;

	if (__builtin_expect(!str || !bits_out, 0))
		return (false);
	bits_out->is_whole = true;
	bits_out->len = ft_strlen(str) * 8;
	bits_out->data = malloc(bits_out->len * sizeof(int));
	if (__builtin_expect(!bits_out->data, 0))
		return (false);
	byte_index = -1;
	while (str[++byte_index])
		char_to_bits(str[byte_index], bits_out->data + byte_index * 8);
	return (true);
}
