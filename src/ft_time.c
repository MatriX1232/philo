/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:45:05 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 14:57:23 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ft_get_time(t_info *info)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (now.tv_usec - info->start.tv_usec);
}
