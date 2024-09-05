/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:27 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/05 13:42:59 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include "colors.h"

//	FT_LIBFT.c
int		ft_strlen(char *str);

// T_PRINT_UTILS.c
void	ft_debuglog(char *msg, char *color);

#endif
