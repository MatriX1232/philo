/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:02:13 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/03 15:36:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*ft_malloc_vars(t_philo *philo)
{
	philo = (t_philo *) malloc(1 * sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->thread = (pthread_t *) malloc(1 * sizeof(pthread_t));
	if (!philo->thread)
		return (NULL);
	philo->data = (t_data *) malloc(1 * sizeof(t_data));
	if (!philo->data)
		return (NULL);
	philo->die_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!philo->die_mutex)
		return (NULL);
	philo->meal_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!philo->meal_mutex)
		return (NULL);
	return (philo);
}

t_philo	*ft_malloc_philo(t_philo *philo, int idx, pthread_mutex_t *pm)
{
	char	*num;
	char	*msg;

	philo = ft_malloc_vars(philo);
	if (!philo)
		return (NULL);
	pthread_mutex_init(philo->die_mutex, NULL);
	pthread_mutex_init(philo->meal_mutex, NULL);
	philo->philo_index = idx;
	philo->print_mutex = pm;
	philo->is_dead = false;
	philo->meal_count = 0;
	philo->start = 0;
	num = ft_itoa(philo->philo_index);
	philo->index = num;
	msg = ft_strjoin(" / ", num);
	write(1, BOLD, ft_strlen(BOLD));
	ft_debuglog_thread(philo, msg, GREEN);
	free(msg);
	return (philo);
}

pthread_mutex_t	**ft_malloc_forks(t_info *info)
{
	int				i;
	unsigned long	p_ms;
	pthread_mutex_t	**forks;

	p_ms = sizeof(pthread_mutex_t *);
	forks = (pthread_mutex_t **) malloc((info->philos_count + 1) * p_ms);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < info->philos_count)
	{
		forks[i] = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
		if (!forks[i])
			return (NULL);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	forks[i] = NULL;
	ft_debuglog("Forks were allocated\n", YELLOW);
	return (forks);
}

void	ft_assign_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		info->philos[i]->left_fork = info->forks[i];
		info->philos[i]->right_fork = info->forks[(i + 1) % info->philos_count];
		i++;
	}
	ft_debuglog("Forks were assigned\n", YELLOW);
}
