/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/01 15:30:24 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_routine(void *v)
{
	t_mix	*mix;
	t_philo	*philo;

	mix = (t_mix *)v;
	if (!mix)
		return (ft_debuglog("MIX not passed to routine function\n", RED), NULL);
	philo = mix->philo;
	while (!is_dead(philo, mix->info))
	{
		if (is_dead(philo, mix->info) || (philo->meal_count > philo->data->times_must_eat && philo->data->times_must_eat != -1))
			pthread_exit(NULL);
		ft_think(philo);
		ft_eat(philo, mix);
		ft_sleep(philo);
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
	pthread_create(philo->thread, NULL, philosopher_routine, mix);
}

void	ft_join_thread(pthread_t *thread)
{
	pthread_join(*thread, NULL);
}

void	ft_free_philo(t_philo *philo)
{
	free(philo->thread);
	free(philo->index);
	free(philo->data);
	pthread_mutex_destroy(philo->die_mutex);
	free(philo->die_mutex);
	free(philo);
}

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (ft_debuglog("BAD ARGUMENTS!\n", RED), EXIT_FAILURE);

	pthread_mutex_t	*print_mutex;
	print_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (EXIT_FAILURE);
	pthread_mutex_init(print_mutex, NULL);
	ft_debuglog("Print mutex is initialized\n", YELLOW);

	t_info	*info;
	info = NULL;
	info = ft_malloc_info(info);
	if (!info)
		return (ft_debuglog("Something wrong with ft_malloc_info\n", RED), EXIT_FAILURE);
	info = ft_parse_info(info, print_mutex, argv);
	if (!info)
		return (ft_debuglog("Something wrong with ft_parse_info\n", RED), EXIT_FAILURE);


	pthread_t	*death_thread;
	death_thread = (pthread_t *) malloc(1 * sizeof(pthread_t));
	if (!death_thread)
		return (ft_debuglog("Death thread not allocated\n", RED), EXIT_FAILURE);
	pthread_create(death_thread, NULL, death_routine, info);


	int	i = 0;
	while (i < info->philos_count)
	{
		ft_run_thread(info->philos[i], info);
		usleep(1000);
		i++;
	}


	for (int i = 0; i < info->philos_count; i++)
		pthread_join(*info->philos[i]->thread, NULL);

	pthread_join(*death_thread, NULL);

	ft_debuglog("Philos thread are joined\n", YELLOW);

	for (int i = 0; i < info->philos_count; i++)
		ft_free_philo(info->philos[i]);

	pthread_mutex_destroy(print_mutex);
	pthread_mutex_destroy(info->somebody_die_mutex);
	free(print_mutex);
	free(info->philos);
	free(info);
	free(death_thread);


	i = 0;
	while (i < info->philos_count)
	{
		pthread_mutex_destroy(info->forks[i]);
		free(info->forks[i]);
		i++;
	}


	ft_debuglog("Philos are freed\n", YELLOW);

	return (EXIT_SUCCESS);
}
