/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/05 13:41:31 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_debuglog(char *msg, char *color)
{
	if (!color)
		write(1, CYAN, ft_strlen(CYAN));
	else
		write(1, color, ft_strlen(color));
	write(1, msg, ft_strlen(msg));
	write(1, END, ft_strlen(END));
}
