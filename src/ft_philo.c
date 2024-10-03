/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 10:36:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_dead(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->die_mutex);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->die_mutex);
	pthread_mutex_lock(info->somebody_die_mutex);
	if (info->somebody_die)
	{
		pthread_mutex_unlock(info->somebody_die_mutex);
		return (true);
	}
	pthread_mutex_unlock(info->somebody_die_mutex);
	return (false);
}

void	ft_print_status(t_philo *philo, t_info *info, char *msg, char *color)
{
	long	cur;

	if (is_dead(philo, info))
		return ;
	cur = get_timestamp() - philo->start;
	pthread_mutex_lock(philo->print_mutex);
	printf("%s%ld %d %s%s\n", color, cur, philo->philo_index, msg, END);
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->die_mutex);
	philo->is_dead = true;
	pthread_mutex_unlock(philo->die_mutex);
}

void	ft_eat(t_philo *philo, t_mix *mix)
{
	ft_take_forks(philo, mix);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_timestamp() - philo->start;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_print_status(philo, mix->info, "is eating", GREEN);
	ft_usleep(philo, philo->data->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_mutex);
}

void	ft_think(t_philo *philo, t_info *info)
{
	ft_print_status(philo, info, "is thinking", YELLOW);
}

void	ft_sleep(t_philo *philo, t_info *info)
{
	ft_print_status(philo, info, "is sleeping", BLUE);
	ft_usleep(philo, philo->data->time_sleep);
}
