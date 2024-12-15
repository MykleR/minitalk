/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:01 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/15 20:26:04 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static t_pid_client	*get_client(void)
{
	static t_pid_client	client = {0};

	return (&client);
}

static void	send_bit(pid_t server_pid, int b)
{
	if (b)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
}

static bool	ft_safe_atopid(const char *str, pid_t	*out)
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

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	t_pid_client	*client;

	(void) context;
	client = get_client();
	client->timeout_counter = CLIENT_TIMEOUT * (sig == SIGUSR1);
	if (sig == SIGUSR2)
		return ;
	send_bit(info->si_pid, ((*client->send) << (client->bit++)) & (1 << 7));
	if (client->bit <= 7)
		return ;
	client->send++;
	client->bit = 0;
}

int	main(int ac, char **av)
{
	struct sigaction	listener;
	t_pid_client		*client;

	client = get_client();
	if (ac != 3 || !ft_safe_atopid(av[1], &client->server))
		return (0);
	client->send = (unsigned char *)av[2];
	client->timeout_counter = CLIENT_TIMEOUT;
	sigemptyset(&listener.sa_mask);
	listener.sa_flags = SA_RESTART | SA_SIGINFO;
	listener.sa_sigaction = sig_handler;
	sigaction(SIGUSR2, &listener, NULL);
	sigaction(SIGUSR1, &listener, NULL);
	client->bit = 1;
	send_bit(client->server, (*client->send) & (1 << 7));
	while (client->timeout_counter--)
		usleep(1000);
}
