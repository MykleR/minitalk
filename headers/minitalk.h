/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:35:47 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/16 20:14:02 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <libft.h>

# define MAX_CLIENTS	0x10000
# define STR_INIT_CAP	4096
# define CLIENT_TIMEOUT 0x1000

typedef struct s_dynamic_str
{
	unsigned char	*data;
	uint32_t		len;
	uint32_t		cap;
}	t_dynamic_str;

typedef struct s_pid_server
{
	t_dynamic_str	string;
	unsigned char	chr;
	uint32_t		count;
	pid_t			client;
}	t_pid_server;

typedef struct s_pid_client
{
	unsigned char	*send;
	uint32_t		bit;
	uint32_t		timeout;
	pid_t			server;
}	t_pid_client;

bool	dynamic_str_create(t_dynamic_str *str);
void	dynamic_str_destroy(t_dynamic_str *str);
void	dynamic_str_add(t_dynamic_str *str, int c);
void	dynamic_str_print(t_dynamic_str *str);
#endif
