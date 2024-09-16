/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 21:16:43 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*myThread(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (!philo)
		return (ft_debuglog("Philo not passed to routine function\n", RED), NULL);
	if (philo->philo_index % 2 == 0)
		usleep(philo->data->time_eat);
	while (!is_dead(philo))
	{
		ft_eat(philo);
		ft_think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	ft_run_thread(t_philo *philo)
{
	pthread_create(philo->thread, NULL, myThread, philo);
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

	int	i = 0;
	while (i < info->philos_count)
	{
		ft_run_thread(info->philos[i]);
		i++;
	}

	for (int i = 0; i < info->philos_count; i++)
		ft_join_thread(info->philos[i]->thread);

	ft_debuglog("Philos thread are joined\n", YELLOW);

	for (int i = 0; i < info->philos_count; i++)
		ft_free_philo(info->philos[i]);

	pthread_mutex_destroy(print_mutex);
	free(print_mutex);
	free(info->philos);
	free(info);

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
