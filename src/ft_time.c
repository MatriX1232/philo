/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:45:05 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 21:56:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ft_get_time(struct timeval start)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (now.tv_usec - start.tv_usec);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int ms)
{
	long int	start_time;

	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < ms)
		usleep(100);
}
