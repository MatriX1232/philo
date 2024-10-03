/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 23:01:51 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_philo(t_philo *philo)
{
	free(philo->thread);
	free(philo->index);
	free(philo->data);
	pthread_mutex_destroy(philo->die_mutex);
	pthread_mutex_destroy(philo->meal_mutex);
	free(philo->die_mutex);
	free(philo->meal_mutex);
	free(philo);
}

static bool	ft_create_run_death(pthread_t **dt, t_info *info)
{
	*dt = (pthread_t *) malloc(1 * sizeof(pthread_t));
	if (!dt)
		return (ft_debuglog("Death thread not allocated\n", RED), EXIT_FAILURE);
	pthread_create(*dt, NULL, death_routine, info);
	return (0);
}

static bool	ft_create_print_m(pthread_mutex_t **print_mutex)
{
	*print_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!(*print_mutex))
		return (false);
	pthread_mutex_init(*print_mutex, NULL);
	ft_debuglog("Print mutex is initialized\n", YELLOW);
	return (true);
}

static void	ft_cleanup(t_info *info, pthread_mutex_t *pm, pthread_t *dt)
{
	int	i;

	i = -1;
	while (++i < info->philos_count)
		pthread_join(*info->philos[i]->thread, NULL);
	pthread_join(*dt, NULL);
	ft_debuglog("All threads are joined\n", YELLOW);
	i = -1;
	while (++i < info->philos_count)
		ft_free_philo(info->philos[i]);
	free(info->philos);
	pthread_mutex_destroy(pm);
	pthread_mutex_destroy(info->somebody_die_mutex);
	free(info->somebody_die_mutex);
	free(pm);
	free(dt);
	i = -1;
	while (++i < info->philos_count)
	{
		pthread_mutex_destroy(info->forks[i]);
		free(info->forks[i]);
	}
	free(info->forks);
	free(info);
	ft_debuglog("Philos are freed\n", YELLOW);
}

int	main(int argc, char *argv[])
{
	pthread_t		*death_thread;
	pthread_mutex_t	*print_mutex;
	t_info			*info;
	int				i;

	if (argc != 5 && argc != 6)
		return (ft_debuglog("BAD ARGUMENTS!\n", RED), EXIT_FAILURE);
	info = NULL;
	info = ft_malloc_info(info);
	if (!info)
		return (ft_debuglog("ERROR in malloc info\n", RED), EXIT_FAILURE);
	print_mutex = NULL;
	if (!ft_create_print_m(&print_mutex))
		return (ft_debuglog("ERROR in ft_create_print_m\n", RED), EXIT_FAILURE);
	info = ft_parse_info(info, print_mutex, argv);
	if (!info)
		return (ft_debuglog("ERROR in ft_parse_info\n", RED), EXIT_FAILURE);
	death_thread = NULL;
	if (ft_create_run_death(&death_thread, info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < info->philos_count)
		ft_run_thread(info->philos[i], info);
	ft_cleanup(info, print_mutex, death_thread);
	return (EXIT_SUCCESS);
}
