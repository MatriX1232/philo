/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 15:39:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_debuglog_thread(t_philo *philo, char *msg, char *color)
{
	if (!philo)
		return ;
	pthread_mutex_lock(philo->print_mutex);
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

void	ft_print_status(t_philo *philo, t_info *info, char *m, char *color)
{
	long	cur;

	if (is_dead(philo, info))
		return ;
	cur = get_timestamp() - philo->start;
	pthread_mutex_lock(philo->print_mutex);
	printf("%s%ld %d %s%s\n", color, cur, philo->philo_index + 1, m, END);
	pthread_mutex_unlock(philo->print_mutex);
}
