/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:33:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 12:40:56 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static void	ft_free_forks(t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (info->forks[i])
// 		free(info->forks[i++]);
// 	free(info->forks);
// }

static void	ft_exit_all(t_info *info)
{
	int	i;

	pthread_mutex_lock(info->somebody_die_mutex);
	info->somebody_die = true;
	pthread_mutex_unlock(info->somebody_die_mutex);
	i = 0;
	// pthread_mutex_lock(info->print_mutex);
	printf("%sPhilosophers are exiting: %s%s", YELLOW, GREEN, BOLD);
	while (i < info->philos_count)
	{
		// pthread_detach(*info->philos[i]->thread);
		// pthread_exit(info->philos[i]->thread);
		printf(" / %d", i);
		i++;
	}
	printf("%s\n", END);
	pthread_mutex_unlock(info->print_mutex);
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
	if (finished == info->philos_count - 1)
	{
		pthread_mutex_lock(info->somebody_die_mutex);
		info->somebody_die = true;
		pthread_mutex_unlock(info->somebody_die_mutex);
		pthread_mutex_lock(info->print_mutex);
		printf("%s%sALl philosophers have eaten enough%s\n", YELLOW, BOLD, END);
		return (1);
	}
	else
		return (0);
}

static bool	ft_is_philo_dead(t_philo *philo)
{
	long	time_last_meal;
	long	cur;

	time_last_meal = get_timestamp() - philo->start - philo->last_meal;
	if (time_last_meal > philo->data->time_die)
	{
		pthread_mutex_lock(philo->print_mutex);
		cur = get_timestamp() - philo->start;
		printf("%s%ld %d died%s\n", RED, cur, philo->philo_index, END);
		ft_philo_died(philo);
		return (true);
	}
	return (false);
}

void	*death_routine(void *v)
{
	t_info	*info;
	int		i;

	info = (t_info *)v;
	printf("%s╔╦╗ ╔═╗ ╔═╗ ╔╦╗ ╦ ╦    ╦ ╔═╗    ╦ ╦ ╔═╗ ╔╦╗ ╔═╗ ╦ ╦ ╦ ╔╗╔ ╔═╗\n", RED);
	printf(" ║║ ║╣  ╠═╣  ║  ╠═╣    ║ ╚═╗    ║║║ ╠═╣  ║  ║   ╠═╣ ║ ║║║ ║ ╦\n");
	printf("═╩╝ ╚═╝ ╩ ╩  ╩  ╩ ╩    ╩ ╚═╝    ╚╩╝ ╩ ╩  ╩  ╚═╝ ╩ ╩ ╩ ╝╚╝ ╚═╝\n%s", END);
	pthread_mutex_unlock(info->print_mutex);
	while (1)
	{
		if (ft_check_philo_meals(info))
			return (ft_exit_all(info), NULL);
		i = 0;
		while (i < info->philos_count)
		{
			if (ft_is_philo_dead(info->philos[i]))
				return (ft_exit_all(info), NULL);
			i++;
		}
	}
	return (NULL);
}
