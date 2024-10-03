/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 23:23:03 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/04 00:02:31 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philos_count)
	{
		pthread_mutex_destroy(info->forks[i]);
		free(info->forks[i]);
	}
	free(info->forks);
}

void	ft_free_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philos_count)
	{
		if (info->philos[i]->thread)
			free(info->philos[i]->thread);
		if (info->philos[i]->index)
			free(info->philos[i]->index);
		if (info->philos[i]->data)
			free(info->philos[i]->data);
		pthread_mutex_destroy(info->philos[i]->die_mutex);
		pthread_mutex_destroy(info->philos[i]->meal_mutex);
		free(info->philos[i]->die_mutex);
		free(info->philos[i]->meal_mutex);
		free(info->philos[i]);
	}
	free(info->philos);
}

void	ft_free_info(t_info *info, pthread_t *dt, pthread_mutex_t *pm)
{
	if (info)
	{
		if (info->somebody_die_mutex)
		{
			pthread_mutex_destroy(info->somebody_die_mutex);
			free(info->somebody_die_mutex);
		}
		free(info);
	}
	if (pm)
	{
		pthread_mutex_destroy(pm);
		free(pm);
	}
	if (dt)
		free(dt);
}
