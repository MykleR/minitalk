/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrouves <mrouves@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:01 by mrouves           #+#    #+#             */
/*   Updated: 2024/12/13 22:49:54 by mrouves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>
#include <stdio.h>

void	send_char_as_bits(int server_pid, char c)
{
	uint32_t	i;

	i = -1;
	while (++i < 8)
	{
		printf("%d ", (bool)((c << i) & (1 << 7)));
		if ((c << i) & (1 << 7))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac != 3 || !ft_safe_atopid(av[1], &server_pid))
		return (0);
	send_char_as_bits(server_pid, av[2][0]);
}
