/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/05 14:15:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*myThread(void *print_mutex)
{
	// (void)print_mutex;
	sleep(1);

	pthread_mutex_lock(print_mutex);
	ft_debuglog("Thread print\n", GREEN);
	pthread_mutex_unlock(print_mutex);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	// (void)argc;
	// (void)argv;
	if (argc != 2)
		return (ft_debuglog("BAD ARGUMENTS!\n", RED), EXIT_FAILURE);

	pthread_mutex_t	*print_mutex;
	print_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (EXIT_FAILURE);
	pthread_mutex_init(print_mutex, NULL);

	pthread_t	threads[atoi(argv[1])];
	ft_debuglog("Before Thread\n", NULL);

	for (int i = 0; i < atoi(argv[1]); i++)
		pthread_create(&threads[i], NULL, myThread, print_mutex);

	for (int i = 0; i < atoi(argv[1]); i++)
		pthread_join(threads[i], NULL);

	ft_debuglog("After Thread\n", NULL);

	return (0);
}
