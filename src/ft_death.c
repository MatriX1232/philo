/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:33:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 15:45:08 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_exit_all(t_info *info)
{
	int	i;

	pthread_mutex_lock(info->somebody_die_mutex);
	info->somebody_die = true;
	pthread_mutex_unlock(info->somebody_die_mutex);
	i = 0;
	printf("%sPhilosophers are exiting: %s%s", YELLOW, GREEN, BOLD);
	while (i < info->philos_count)
	{
		printf(" / %d", i);
		i++;
	}
	printf("%s\n", END);
	pthread_mutex_unlock(info->print_mutex);
}

int	ft_check_philo_meals(t_info *info)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < info->philos_count)
	{
		if (info->philos[i]->meal_count >= info->times_must_eat)
			finished++;
		i++;
	}
	if (finished == info->philos_count - 1)
	{
		pthread_mutex_lock(info->somebody_die_mutex);
		info->somebody_die = true;
		pthread_mutex_unlock(info->somebody_die_mutex);
		pthread_mutex_lock(info->print_mutex);
		printf("%s%sALl philosophers have eaten enough%s\n", YELLOW, BOLD, END);
		return (1);
	}
	else
		return (0);
}

bool	ft_is_philo_dead(t_philo *philo)
{
	long	time_last_meal;
	long	cur;

	time_last_meal = get_timestamp() - philo->start - philo->last_meal;
	if (time_last_meal > philo->data->time_die)
	{
		pthread_mutex_lock(philo->print_mutex);
		cur = get_timestamp() - philo->start;
		printf("%s%ld %d died%s\n", RED, cur, philo->philo_index, END);
		ft_philo_died(philo);
		return (true);
	}
	return (false);
}
