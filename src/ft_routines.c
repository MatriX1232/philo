/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:42:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:54 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_one_philo(t_philo *philo, t_info *info)
{
	ft_print_status(philo, info, "is thinking", YELLOW);
	ft_print_status(philo, info, "has taken a fork", CYAN);
	ft_usleep(philo, info->time_die);
	ft_philo_died(philo);
}

void	*philo_routine(void *v)
{
	t_mix	*mix;
	t_philo	*philo;
	bool	case_one;
	bool	case_two;

	mix = (t_mix *)v;
	if (!mix)
		return (ft_debuglog("MIX not passed to routine function\n", RED), NULL);
	if (mix->info->philos_count == 1)
		return (ft_one_philo(mix->philo, mix->info), NULL);
	philo = mix->philo;
	while (!is_dead(philo, mix->info))
	{
		case_one = philo->meal_count > philo->data->times_must_eat;
		case_two = philo->data->times_must_eat != -1;
		if (is_dead(philo, mix->info))
			pthread_exit(NULL);
		else if (case_one && case_two)
			pthread_exit(NULL);
		ft_think(philo, mix->info);
		ft_eat(philo, mix);
		ft_sleep(philo, mix->info);
	}
	free(mix);
	return (NULL);
}

void	ft_run_thread(t_philo *philo, t_info *info)
{
	t_mix	*mix;

	mix = (t_mix *) malloc(1 * sizeof(t_mix));
	if (!mix)
		return (ft_debuglog("MIX not allocated\n", RED));
	mix->philo = philo;
	mix->info = info;
	pthread_create(philo->thread, NULL, philo_routine, mix);
}

void	*death_routine(void *v)
{
	t_info	*info;
	int		i;

	info = (t_info *)v;
	printf("%s", RED);
	printf("╔╦╗ ╔═╗ ╔═╗ ╔╦╗ ╦ ╦    ╦ ╔═╗    ╦ ╦ ╔═╗ ╔╦╗ ╔═╗ ╦ ╦ ╦ ╔╗╔ ╔═╗\n");
	printf(" ║║ ║╣  ╠═╣  ║  ╠═╣    ║ ╚═╗    ║║║ ╠═╣  ║  ║   ╠═╣ ║ ║║║ ║ ╦\n");
	printf("═╩╝ ╚═╝ ╩ ╩  ╩  ╩ ╩    ╩ ╚═╝    ╚╩╝ ╩ ╩  ╩  ╚═╝ ╩ ╩ ╩ ╝╚╝ ╚═╝\n");
	printf("%s", END);
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
