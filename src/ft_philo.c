/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 14:49:39 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

void	ft_eat(t_info *info, t_philo *philo)
{
	// char	*msg;
	// char	*tmp;

	if (!philo->right_fork || !philo->left_fork)
		return ;
	// tmp = ft_strjoin("Philosopher ", philo->index);
	// msg = ft_strjoin
	printf("Current time: %ld\n", ft_get_time());
	// ft_debuglog_thread(philo, "")
	usleep(info->time_eat);
}
