/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:31:48 by cmauley           #+#    #+#             */
/*   Updated: 2026/04/07 15:59:23 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile sig_atomic_t	g_ack;
static void	ack_handler(int signum);
static int	is_error(char *error);
static int	parse_pid(char *pid);
static void	send_char(int pid, unsigned char c);

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac != 3)
		return (is_error("Invalid number of arguments"));
	if (av[2][0] == '\0')
		return (is_error("Empty message"));
	signal(SIGUSR1, ack_handler);
	pid = parse_pid(av[1]);
	if (pid == -1)
		return (is_error("Invalid PID"));
	if (kill(pid, 0) == -1)
		return (is_error("Process does not exist"));
	while (av[2][i])
	{
		send_char(pid, av[2][i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack = 1;
}

static int	is_error(char *error)
{
	ft_printf("%s\n", error);
	return (1);
}

static int	parse_pid(char *pid)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (pid[i])
	{
		if (ft_isdigit(pid[i]) != 1)
			return (-1);
		i++;
	}
	result = ft_atoi(pid);
	return (result);
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
		while (g_ack == 0)
			pause();
		bit_index++;
	}
}
