/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 15:00:09 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*myThread(void *p)
{
	sleep(1);
	t_philo	*philo;
	char	*msg;

	philo = (t_philo *)p;
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
	info = (t_info *) malloc(1 * sizeof(t_info *));
	if (!info)
		return (NULL);
	info->philos = NULL;
	info->time_die = 0;
	info->time_eat = 0;
	info->time_think = 0;
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


	int number_philos = atoi(argv[1]);
	int	i = 0;
	t_philo	**philos;
	philos = (t_philo **) malloc(number_philos * sizeof(t_philo *));
	ft_debuglog("Initialized philo with index: ", YELLOW);
	while (i < number_philos)
	{
		philos[i] = NULL;
		philos[i] = ft_malloc_philo(philos[i], i, print_mutex);
		if (philos[i] == NULL)
			return (ft_debuglog("Problem with philo malloc\n", RED), EXIT_FAILURE);
		i++;
	}

	ft_debuglog("\nPhilos are malloced\n", YELLOW);

	for (int i = 0; i < number_philos; i++)
		ft_run_thread(philos[i]);

	pthread_mutex_lock(print_mutex);
	ft_debuglog("Philos thread are running\n", YELLOW);
	pthread_mutex_unlock(print_mutex);

	for (int i = 0; i < number_philos; i++)
		ft_join_thread(philos[i]->thread);

	ft_debuglog("Philos thread are joined\n", YELLOW);

	for (int i = 0; i < number_philos; i++)
		ft_free_philo(philos[i]);

	free(print_mutex);
	free(philos);

	ft_debuglog("Philos are freed\n", YELLOW);

	return (EXIT_SUCCESS);
}
