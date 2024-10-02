/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:33:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/02 14:54:45 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_exit_all(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(info->philos[0]->print_mutex);
	printf("%sPhilosophers are exiting: %s", YELLOW, GREEN);
	while (i < info->philos_count)
	{
		pthread_detach(*info->philos[i]->thread);
		pthread_exit(info->philos[i]->thread);
		printf("/ %d ", i);
		i++;
	}
	printf("%s\n", END);
	pthread_mutex_unlock(info->philos[0]->print_mutex);
}

int	ft_check_philo_meals(t_info *info)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < info->philos_count)
	{
		if (info->philos[i]->meal_count >= info->times_must_eat)
			finished++;
		i++;
	}
	if (finished == info->philos_count)
	{
		ft_print_status(info->philos[0], "All philosophers have eaten enough", GREEN);
		return (1);
	}
	else
		return (0);
}

void	*death_routine(void *v)
{
	t_info	*info;
	t_philo	*philo;
	int		i;

	info = (t_info *)v;
	printf("%s╔╦╗╔═╗╔═╗╔╦╗╦ ╦  ╦╔═╗  ╦ ╦╔═╗╔╦╗╔═╗╦ ╦╦╔╗╔╔═╗\n", RED);
	printf(" ║║║╣ ╠═╣ ║ ╠═╣  ║╚═╗  ║║║╠═╣ ║ ║  ╠═╣║║║║║ ╦\n");
	printf("═╩╝╚═╝╩ ╩ ╩ ╩ ╩  ╩╚═╝  ╚╩╝╩ ╩ ╩ ╚═╝╩ ╩╩╝╚╝╚═╝\n%s", END);
	while (1)
	{
		// if (ft_check_philo_meals(info))
		// 	return (ft_exit_all(info), NULL);
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
				return (ft_exit_all(info), NULL);
			}
			i++;
		}
	}
	return (NULL);
}
