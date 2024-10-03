/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:45:05 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 10:44:22 by msolinsk         ###   ########.fr       */
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

void	ft_usleep(t_philo *philo, long int ms)
{
	long int	start_time;
	long		time_last_meal;

	// while (ms / 2 > 10)
	// {
	// 	usleep(ms * 1000);
	// 	ms /= 2;
	// }


	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < ms)
	{
		time_last_meal = get_timestamp() - philo->start - philo->last_meal;
		if (time_last_meal > philo->data->time_die)
			return (ft_philo_died(philo));
		usleep(1000);
	}
}
