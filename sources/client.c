/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:01 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/16 20:19:16 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static t_pid_client	*get_client(void)
{
	static t_pid_client	client = {0};

	return (&client);
}

static void	send_bit(pid_t pid, int b)
{
	if (b)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	t_pid_client	*client;

	(void) context;
	client = get_client();
	client->timeout = CLIENT_TIMEOUT * (sig == SIGUSR1);
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
	int					pid;

	client = get_client();
	if (ac != 3 || !ft_safe_atoi(av[1], &pid) || pid <= 0)
		return (0);
	client->server = (pid_t)pid;
	client->send = (unsigned char *)av[2];
	client->timeout = CLIENT_TIMEOUT;
	listener.sa_flags = SA_RESTART | SA_SIGINFO;
	listener.sa_sigaction = sig_handler;
	sigemptyset(&listener.sa_mask);
	sigaction(SIGUSR2, &listener, NULL);
	sigaction(SIGUSR1, &listener, NULL);
	client->bit = 1;
	send_bit(client->server, (*client->send) & (1 << 7));
	while (client->timeout--)
		usleep(1000);
}
