/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/01 15:29:20 by msolinsk         ###   ########.fr       */
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

void	ft_print_status(t_philo *philo, char *msg, char *color)
{
	long	cur;

	cur = get_timestamp() - philo->start;
	pthread_mutex_lock(philo->print_mutex);
	printf("%s%ld %d %s%s\n", color, cur, philo->philo_index, msg, END);
	pthread_mutex_unlock(philo->print_mutex);
}

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

static int	ft_am_i_hungrier(t_philo *philo, t_mix *mix)
{
	long	last_current;
	long	last_prev;
	long	last_next;

	last_current = philo->last_meal;
	last_prev = ft_get_previous_last_meal(philo->philo_index, mix->info);
	last_next = ft_get_next_last_meal(philo->philo_index, mix->info);
	if (last_current < last_prev)
		return (0);
	else if (last_current < last_next)
		return (0);
	return (1);
}

static void	ft_lock_forks(t_philo *philo)
{
	if (philo->philo_index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
	}
}

static void	ft_take_forks(t_philo *philo, t_mix *mix)
{
	while (!is_dead(philo, mix->info))
	{
		if (ft_am_i_hungrier(philo, mix))
		{
			ft_lock_forks(philo);
			break ;
		}
		else
			ft_usleep(philo, philo->data->time_eat / 10);
	}
}

void	ft_philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->die_mutex);
	philo->is_dead = true;
	pthread_mutex_unlock(philo->die_mutex);
}

void	ft_eat(t_philo *philo, t_mix *mix)
{
	// long	time_last_meal;

	// time_last_meal = get_timestamp() - philo->start - philo->last_meal;
	// if (time_last_meal > philo->data->time_die)
	// 	return (ft_philo_died(philo));
	ft_take_forks(philo, mix);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_timestamp() - philo->start;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_print_status(philo, "is eating", GREEN);
	ft_usleep(philo, philo->data->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_mutex);
}

void	ft_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking", YELLOW);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping", BLUE);
	ft_usleep(philo, philo->data->time_sleep);
}
