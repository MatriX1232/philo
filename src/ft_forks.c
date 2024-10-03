/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:37:34 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 15:38:14 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_lock_fleft(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, info, "has taken a fork", CYAN);
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, info, "has taken a fork", CYAN);
}

static void	ft_lock_fright(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, info, "has taken a fork", CYAN);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, info, "has taken a fork", CYAN);
}

static int	ft_am_i_hungrier(t_philo *philo, t_mix *mix)
{
	long	last_current;
	long	last_prev;
	long	last_next;

	last_current = philo->last_meal;
	last_prev = ft_get_previous_last_meal(philo->philo_index, mix->info);
	last_next = ft_get_next_last_meal(philo->philo_index, mix->info);
	if (last_current <= last_prev && last_current <= last_next)
		return (1);
	return (0);
}

static void	ft_lock_forks(t_philo *philo, t_info *info)
{
	if ((philo->philo_index) % 2 == 0)
		ft_lock_fright(philo, info);
	else
		return (ft_lock_fleft(philo, info));
}

void	ft_take_forks(t_philo *philo, t_mix *mix)
{
	while (!is_dead(philo, mix->info))
	{
		if (ft_am_i_hungrier(philo, mix))
		{
			ft_lock_forks(philo, mix->info);
			break ;
		}
		else
			ft_usleep(philo, 1);
	}
}
