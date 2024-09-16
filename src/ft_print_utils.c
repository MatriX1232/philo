/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 16:31:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_debuglog_thread(t_philo *philo, char *msg, char *color)
{
	if (!philo)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	usleep(300);
	if (!color)
		write(1, CYAN, ft_strlen(CYAN));
	else
		write(1, color, ft_strlen(color));
	write(1, msg, ft_strlen(msg));
	write(1, END, ft_strlen(END));
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_debuglog(char *msg, char *color)
{
	if (!color)
		write(1, CYAN, ft_strlen(CYAN));
	else
		write(1, color, ft_strlen(color));
	write(1, msg, ft_strlen(msg));
	write(1, END, ft_strlen(END));
}
