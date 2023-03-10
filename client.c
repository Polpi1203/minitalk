/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaucher <afaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:22:43 by polpi             #+#    #+#             */
/*   Updated: 2023/01/04 08:52:46 by afaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	send_signal_end(int pid, char c)
{
	int				j;
	unsigned char	bit;

	j = -1;
	while (++j < 8)
	{
		bit = (c >> j & 1);
		if (bit == 0)
			kill(pid, SIGUSR2);
		else if (bit == 1)
			kill(pid, SIGUSR1);
		usleep(60);
	}
}

void	send_signal(int pid, char *str)
{
	int				i;
	int				j;
	unsigned char	bit;

	i = -1;
	while (str[++i] != '\0')
	{
		j = -1;
		while (++j < 8)
		{
			bit = (str[i] >> j & 1);
			if (bit == 0)
				kill(pid, SIGUSR2);
			else if (bit == 1)
				kill(pid, SIGUSR1);
			usleep(60);
		} 
	}
	send_signal_end(pid, 0);
}

int main(int ac, char **av)
{
	(void)ac;
	int	pid;


	pid = ft_atoi(av[1]);
	if (ac == 3)
		send_signal(pid, av[2]);
	else
		ft_printf("The first arg should be the server pid, the second one the message.\n");
}