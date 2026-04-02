/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:31:48 by cmauley           #+#    #+#             */
/*   Updated: 2026/03/31 03:12:32 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile sig_atomic_t	g_ack;

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack = 1;
}

static void	send_char(int pid, unsigned char c)
{
	int	bit_index;

	bit_index = 0;
	while (bit_index != 8)
	{
		g_ack = 0;
		if ((c >> bit_index & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			pause();
		bit_index++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac != 3)
		return (1);
	signal(SIGUSR1, ack_handler);
	pid = ft_atoi(av[1]);
	while (av[2][i])
	{
		send_char(pid, av[2][i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
