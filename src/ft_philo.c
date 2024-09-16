/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 16:40:50 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_info *info, t_philo *philo)
{
	char	*msg;

	if (!philo->right_fork || !philo->left_fork)
		return ;

	msg = ft_strjoin(philo->index, " is eating\n");
	pthread_mutex_lock(philo->print_mutex);
	write(1, GREEN, 5);
	ft_putnbr_fd((int)ft_get_time(info), 1);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, END, 5);
	pthread_mutex_unlock(philo->print_mutex);
	free(msg);
	usleep(info->time_eat);
}
