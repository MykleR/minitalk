/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:38:18 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/15 20:10:59 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static bool	unordered_get(t_pid_server *server, pid_t key,
		uint32_t *out_id, bool *is_new)
{
	uint32_t		start;

	if (__builtin_expect(!server || !key || !out_id
			|| server->len >= MAX_CLIENTS, 0))
		return (false);
	*out_id = key & (MAX_CLIENTS - 1);
	start = *out_id;
	while (server->clients[*out_id].key
		&& server->clients[*out_id].key != key)
	{
		*out_id = (*out_id + 1) & (MAX_CLIENTS - 1);
		if (__builtin_expect(*out_id == start, 0))
			return (false);
	}
	*is_new = !server->clients[*out_id].key;
	server->len += *is_new;
	server->clients[*out_id].key = key;
	return (true);
}

static bool	manage_client(t_pid_reader *client,	t_dynamic_str *str, int sig)
{
	bool	is_end;

	is_end = false;
	client->chr = (client->chr << 1) | (sig == SIGUSR2);
	if (++client->count >= 8)
	{
		is_end = !client->chr;
		dynamic_str_add(str, client->chr);
		client->count = 0;
		client->chr = 0;
	}
	if (!is_end)
		kill(client->key, SIGUSR1);
	return (!is_end);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static t_pid_server	server = {0};
	uint32_t			id;
	bool				is_new;

	(void) context;
	if (!unordered_get(&server, info->si_pid, &id, &is_new))
		return ;
	if (__builtin_expect(is_new, 0))
		dynamic_str_create(server.strings + id);
	if (__builtin_expect(manage_client(
				server.clients + id, server.strings + id, sig), 1))
		return ;
	server.clients[id].key = 0;
	dynamic_str_print(server.strings + id);
	dynamic_str_destroy(server.strings + id);
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
	sigemptyset(&listener.sa_mask);
	sigemptyset(&exit_gate.sa_mask);
	listener.sa_flags = SA_RESTART | SA_SIGINFO;
	exit_gate.sa_flags = 0;
	listener.sa_sigaction = sig_handler;
	exit_gate.sa_sigaction = exit_handler;
	sigaction(SIGUSR2, &listener, NULL);
	sigaction(SIGUSR1, &listener, NULL);
	sigaction(SIGINT, &exit_gate, NULL);
	while (1)
		pause();
}
