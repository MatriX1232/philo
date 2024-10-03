/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/04 00:06:05 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ft_create_run_death(pthread_t **dt, t_info *info)
{
	*dt = (pthread_t *) malloc(1 * sizeof(pthread_t));
	if (!*dt)
	{
		ft_free_forks(info);
		ft_free_info(info, *dt, info->print_mutex);
	}
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
	ft_free_philos(info);
	ft_free_forks(info);
	ft_free_info(info, dt, pm);
	ft_debuglog("Philos are freed\n", YELLOW);
}

int	main(int argc, char *argv[])
{
	pthread_t		*t_death;
	pthread_mutex_t	*m_print;
	t_info			*info;
	int				i;

	if (argc != 5 && argc != 6)
		return (ft_debuglog("BAD ARGUMENTS!\n", RED), EXIT_FAILURE);
	info = NULL;
	info = ft_malloc_info(info);
	if (!info)
		return (ft_debuglog("ERROR in malloc info\n", RED), EXIT_FAILURE);
	m_print = NULL;
	if (!ft_create_print_m(&m_print))
		return (ft_debuglog("ERROR in ft_create_print_m\n", RED), EXIT_FAILURE);
	info = ft_parse_info(info, m_print, argv);
	if (!info)
		return (ft_debuglog("ERROR in ft_parse_info\n", RED), EXIT_FAILURE);
	t_death = NULL;
	if (ft_create_run_death(&t_death, info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < info->philos_count)
		ft_run_thread(info->philos[i], info);
	ft_cleanup(info, m_print, t_death);
	return (EXIT_SUCCESS);
}
