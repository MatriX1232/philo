/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:33:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/01 13:02:55 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_print_start(void)
{
	printf("%s╔╦╗╔═╗╔═╗╔╦╗╦ ╦  ╦╔═╗  ╦ ╦╔═╗╔╦╗╔═╗╦ ╦╦╔╗╔╔═╗\n", RED);
	printf(" ║║║╣ ╠═╣ ║ ╠═╣  ║╚═╗  ║║║╠═╣ ║ ║  ╠═╣║║║║║ ╦\n");
	printf("═╩╝╚═╝╩ ╩ ╩ ╩ ╩  ╩╚═╝  ╚╩╝╩ ╩ ╩ ╚═╝╩ ╩╩╝╚╝╚═╝\n%s", END);
}

static void	ft_detach_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		pthread_detach(*info->philos[i]->thread);
		i++;
	}
}

void	*death_routine(void *v)
{
	t_info	*info;
	t_philo	*philo;
	int		i;

	info = (t_info *)v;
	ft_print_start();
	while (1)
	{
		i = 0;
		while (i < info->philos_count)
		{
			philo = info->philos[i];
			if (is_dead(philo, info))
			{
				ft_print_status(philo, "died", RED);
				pthread_mutex_lock(info->somebody_die_mutex);
				info->somebody_die = true;
				pthread_mutex_unlock(info->somebody_die_mutex);
				// pthread_mutex_lock(philo->print_mutex);
				return (ft_detach_all(info), NULL);
			}
			i++;
		}
	}
	return (NULL);
}
