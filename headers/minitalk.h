/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:35:47 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/15 20:00:18 by mrouves          ###   ########.fr       */
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


typedef struct s_pid_reader
{
	unsigned char	chr;
	int				count;
	pid_t			key;
}	t_pid_reader;

typedef struct s_pid_server
{
	t_pid_reader	clients[MAX_CLIENTS];
	t_dynamic_str	strings[MAX_CLIENTS];
	uint32_t		len;
}	t_pid_server;

typedef struct s_pid_client
{
	unsigned char	*send;
	int				bit;
	int				timeout_counter;
}	t_pid_client;

bool	dynamic_str_create(t_dynamic_str *str);
void	dynamic_str_destroy(t_dynamic_str *str);
void	dynamic_str_add(t_dynamic_str *str, int c);
void	dynamic_str_print(t_dynamic_str *str);

bool	ft_safe_atopid(const char *str, pid_t *out);
#endif
