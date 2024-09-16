/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 16:35:55 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*myThread(void *p)
{
	t_philo	*philo;
	char	*msg;

	sleep(1);
	philo = (t_philo *)p;
	if (!philo)
		return (ft_debuglog("Philo not passed to routine function\n", RED), NULL);
	msg = ft_strjoin("Hello from thread: ", philo->index);
	ft_debuglog_thread(philo, msg, CYAN);
	ft_debuglog_thread(philo, "\n", NULL);
	free(msg);
	return (NULL);
}

t_philo	*ft_malloc_philo(t_philo *philo, int philo_index, pthread_mutex_t *print_mutex)
{
	char	*num;
	char	*msg;

	philo = (t_philo *) malloc(1 * sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->thread = (pthread_t *) malloc(1 * sizeof(pthread_t));
	if (!philo->thread)
		return (NULL);
	philo->philo_index = philo_index;
	philo->print_mutex = print_mutex;
	philo->left_fork = NULL;
	philo->right_fork = NULL;

	num = ft_itoa(philo->philo_index);
	philo->index = num;
	msg = ft_strjoin(" / ", num);
	ft_debuglog_thread(philo, msg, GREEN);
	free(msg);
	return (philo);
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
	free(philo);
}

t_info	*ft_malloc_info(t_info *info)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	info = (t_info *) malloc(1 * sizeof(t_info));
	if (!info)
		return (NULL);
	info->philos = NULL;
	info->philos_count = 0;
	info->time_die = 0;
	info->time_eat = 0;
	info->time_think = 0;
	info->start = start;
	return (info);
}

t_info	*ft_parse_info(t_info *info, pthread_mutex_t *pm, char *argv[])
{
	int		philo_count;
	int		i;
	t_philo	**philos;

	philo_count = ft_atoi(argv[1]);
	info->philos_count = philo_count;
	philos = (t_philo **) malloc((philo_count + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	ft_debuglog("Initialized philosopher with number: ", YELLOW);
	i = 0;
	while (i < philo_count)
	{
		philos[i] = NULL;
		philos[i] = ft_malloc_philo(philos[i], i, pm);
		if (philos[i] == NULL)
			return (ft_debuglog("Problem with philo malloc\n", RED), NULL);
		i++;
	}
	ft_debuglog("\nPhilos are malloced\n", YELLOW);
	philos[i] = NULL;
	info->philos = philos;
	ft_debuglog("Info was parsed\n", YELLOW);
	return (info);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
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

	pthread_mutex_lock(print_mutex);
	ft_debuglog("Philos thread are running\n", YELLOW);
	pthread_mutex_unlock(print_mutex);

	for (int i = 0; i < info->philos_count; i++)
		ft_join_thread(info->philos[i]->thread);

	ft_debuglog("Philos thread are joined\n", YELLOW);

	for (int i = 0; i < info->philos_count; i++)
		ft_free_philo(info->philos[i]);

	free(print_mutex);
	free(info->philos);
	free(info);

	ft_debuglog("Philos are freed\n", YELLOW);

	return (EXIT_SUCCESS);
}
