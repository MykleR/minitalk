/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:38:18 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/16 20:23:32 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static bool	manage_client(t_pid_server *server, int sig)
{
	bool	is_end;

	is_end = false;
	server->chr = (server->chr << 1) | (sig == SIGUSR2);
	if (++server->count >= 8)
	{
		is_end = !server->chr;
		dynamic_str_add(&server->string, server->chr);
		server->count = 0;
		server->chr = 0;
	}
	if (!is_end)
		kill(server->client, SIGUSR1);
	return (!is_end);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_pid_server	server = {0};

	(void) context;
	if (server.client && server.client != info->si_pid)
		return ;
	if (__builtin_expect(!server.client, 0))
		dynamic_str_create(&server.string);
	server.client = info->si_pid;
	if (__builtin_expect(manage_client(&server, sig), 1))
		return ;
	server.client = 0;
	dynamic_str_print(&server.string);
	dynamic_str_destroy(&server.string);
	kill(info->si_pid, SIGUSR2);
}

static void	exit_handler(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	exit(1);
}

int	main(void)
{
	struct sigaction	listener;
	struct sigaction	exit_gate;

	ft_printf(1, "%d\n", (int)getpid());
	exit_gate.sa_flags = SA_RESTART | SA_SIGINFO;
	listener.sa_flags = SA_RESTART | SA_SIGINFO;
	listener.sa_sigaction = sig_handler;
	exit_gate.sa_sigaction = exit_handler;
	sigemptyset(&listener.sa_mask);
	sigemptyset(&exit_gate.sa_mask);
	sigaction(SIGUSR2, &listener, NULL);
	sigaction(SIGUSR1, &listener, NULL);
	sigaction(SIGINT, &exit_gate, NULL);
	while (1)
		pause();
}
