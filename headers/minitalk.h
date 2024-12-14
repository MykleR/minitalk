/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:35:47 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/14 20:22:23 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_bits_str
{
	int			*data;
	uint32_t	len;
	bool		is_whole;
}	t_bits_str;

void	char_to_bits(char c, int *bits);
bool	bits_to_string(const t_bits_str *bits, char **str_out);
bool	string_to_bits(const char *str, t_bits_str *bits_out);

bool	ft_safe_atopid(const char *str, pid_t *out);
size_t	ft_strlen(const char *str);
#endif
