/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 23:44:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->die_mutex);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->die_mutex);
	return (false);
}

void	ft_print_status(t_philo *philo, char *msg, char *color)
{
	long	cur;

	cur = get_timestamp() - philo->start;
	pthread_mutex_lock(philo->print_mutex);
	if (!is_dead(philo))
		printf("%s%ld %d %s%s\n", color, cur, philo->philo_index, msg, END);
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_eat(t_philo *philo)
{
	if (philo->left_fork != NULL && philo->right_fork != NULL)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork", CYAN);
	}
	else
	{
		char	*msg;

		msg = ft_strjoin(philo->index, " << ERROR: Forks are not assigned\n");
		ft_debuglog_thread(philo, msg, RED);
		free(msg);
		return ;
	}
	if (philo->last_meal - get_timestamp() >= philo->data->time_die)
	{
		ft_print_status(philo, "died", RED);
		pthread_mutex_lock(philo->die_mutex);
		philo->is_dead = true;
		pthread_mutex_unlock(philo->die_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	ft_print_status(philo, "is eating", GREEN);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal = get_timestamp();
	philo->meal_count++;
}

void	ft_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking", YELLOW);
	ft_usleep(philo->data->time_eat);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping", BLUE);
	ft_usleep(philo->data->time_sleep);
}
