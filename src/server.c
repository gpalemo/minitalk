/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:30:57 by cmauley           #+#    #+#             */
/*   Updated: 2026/03/31 03:41:24 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit_index;
	static int	character;

	(void)context;
	if (signum == SIGUSR2)
		character |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (character == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", (char)character);
		bit_index = 0;
		character = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_sigaction = signal_handler;
	sigemptyset(&signal_received.sa_mask);
	signal_received.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		pause();
	return (0);
}