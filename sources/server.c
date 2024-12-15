/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:38:18 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/14 20:43:26 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>
#include <libft.h>

#define	MAX_CLIENTS	0x10000

typedef struct s_pid_reader
{
	int			bchar;
	int			count;
	pid_t		key;
}	t_pid_reader;

bool unordered_get(t_pid_reader *tab, pid_t key, uint32_t *out_index)
{
	static uint32_t	nb_set = 0;
	uint32_t		start;

	if (__builtin_expect(!tab || !key || !out_index || nb_set >= MAX_CLIENTS, 0))
		return (false);
	*out_index = key & (MAX_CLIENTS - 1);
	start = *out_index;
	while (tab[*out_index].key && tab[*out_index].key != key)
	{
		*out_index = (*out_index + 1) & (MAX_CLIENTS - 1);
		if (*out_index == start)
			return (false);
	}
	nb_set += !tab[*out_index].key;
	tab[*out_index].key = key;
	return (true);
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static t_pid_reader	bits[MAX_CLIENTS] = {0};
	uint32_t			client;
	
	(void) context;
	if (!unordered_get(bits, info->si_pid, &client))
		return ;
	bits[client].bchar = (bits[client].bchar << 1) | (signum == SIGUSR2);
	bits[client].count++;
	if (bits[client].count <= 7)
		return ;
	write(1, &bits[client].bchar, 1);
	if (!bits[client].bchar)
		ft_memset(bits + client, 0, sizeof(t_pid_reader));
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf(1,"%d\n", (int)getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
		pause();
}
