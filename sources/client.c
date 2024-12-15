/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:01 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/15 19:56:46 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>


static t_pid_client	client = {0};

static void send_bit(pid_t server_pid, int b)
{
	if (b)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void) context;

	client.timeout_counter = CLIENT_TIMEOUT * (sig == SIGUSR1);
	if (sig == SIGUSR2)
		return ;
	usleep(1000);
	send_bit(info->si_pid, ((*client.send) << (client.bit++)) & (1 << 7));
	if (client.bit <= 7)
		return;
	client.send++;
	client.bit = 0;
}

int	main(int ac, char **av)
{
	struct sigaction	listener;
	pid_t				server_pid;

	if (ac != 3 || !ft_safe_atopid(av[1], &server_pid))
		return (0);
	client.bit = 1;
	client.send = (unsigned char *)av[2];
	client.timeout_counter = CLIENT_TIMEOUT;
	sigemptyset(&listener.sa_mask);
	listener.sa_flags = SA_RESTART | SA_SIGINFO;
	listener.sa_sigaction = sig_handler;
	sigaction(SIGUSR2, &listener, NULL);
	sigaction(SIGUSR1, &listener, NULL);
	send_bit(server_pid, (*client.send) & (1 << 7));
	while (client.timeout_counter--)
		usleep(1000);
}
