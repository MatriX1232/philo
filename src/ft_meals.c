/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:42:05 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/02 12:42:35 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_get_last_meal(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->meal_mutex);
	return (last_meal);
}

long	ft_get_previous_last_meal(int current, t_info *info)
{
	int		previous;

	if (current == 0)
		previous = info->philos_count - 1;
	else
		previous = current - 1;
	return (ft_get_last_meal(info->philos[previous]));
}

long	ft_get_next_last_meal(int current, t_info *info)
{
	int		next;

	if (current == info->philos_count - 1)
		next = 0;
	else
		next = current + 1;
	return (ft_get_last_meal(info->philos[next]));
}
