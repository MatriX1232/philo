/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:02:13 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/01 17:35:16 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*ft_malloc_philo(t_philo *philo, int philo_index, pthread_mutex_t *pm)
{
	char	*num;
	char	*msg;

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
	pthread_mutex_init(philo->die_mutex, NULL);
	pthread_mutex_init(philo->meal_mutex, NULL);
	philo->philo_index = philo_index;
	philo->print_mutex = pm;
	philo->is_dead = false;
	philo->meal_count = 0;

	num = ft_itoa(philo->philo_index);
	philo->index = num;
	msg = ft_strjoin(" / ", num);
	ft_debuglog_thread(philo, msg, GREEN);
	free(msg);
	return (philo);
}

t_info	*ft_malloc_info(t_info *info)
{
	info = (t_info *) malloc(1 * sizeof(t_info));
	if (!info)
		return (NULL);
	info->philos = NULL;
	info->forks = NULL;
	info->philos_count = 0;
	info->time_die = 0;
	info->time_eat = 0;
	info->times_must_eat = 0;
	info->time_sleep = 0;
	info->start = get_timestamp();
	info->somebody_die_mutex = (pthread_mutex_t *) malloc(1 * sizeof(pthread_mutex_t));
	if (!info->somebody_die_mutex)
		return (NULL);
	pthread_mutex_init(info->somebody_die_mutex, NULL);
	info->somebody_die = false;
	return (info);
}

pthread_mutex_t	**ft_malloc_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = (pthread_mutex_t **) malloc((info->philos_count + 1) * sizeof(pthread_mutex_t *));
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
	return (forks);
}

void	ft_assign_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos_count)
	{
		if (i == 0)
		{
			info->philos[0]->left_fork = info->forks[info->philos_count - 1];
			info->philos[0]->right_fork = info->forks[0];
		}
		else if (i == info->philos_count - 1)
		{
			info->philos[i]->left_fork = info->forks[i - 1];
			info->philos[i]->right_fork = info->forks[0];
		}
		else
		{
			info->philos[i]->left_fork = info->forks[i];
			info->philos[i]->right_fork = info->forks[i + 1];
		}
		i++;
	}
	ft_debuglog("Forks were assigned\n", YELLOW);
}

t_info	*ft_parse_info(t_info *info, pthread_mutex_t *pm, char *argv[])
{
	int		philo_count;
	int		i;
	t_philo	**philos;

	philo_count = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	if (philo_count < 1 || info->time_die < 1 || info->time_eat < 1 || info->time_sleep < 1 || (argv[5] && info->times_must_eat < 1))
		return (ft_debuglog("Invalid arguments\n", RED), NULL);
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
		philos[i]->start = info->start;
		philos[i]->data->philos_count = info->philos_count;
		philos[i]->data->time_die = info->time_die;
		philos[i]->data->time_eat = info->time_eat;
		philos[i]->data->times_must_eat = info->times_must_eat;
		philos[i]->data->time_sleep = info->time_sleep;
		i++;
	}
	ft_debuglog("\nPhilos are malloced\n", YELLOW);
	philos[i] = NULL;
	info->philos = philos;
	info->forks = ft_malloc_forks(info);
	ft_debuglog("Forks are malloced\n", YELLOW);
	ft_debuglog("Info was parsed\n", YELLOW);
	ft_assign_forks(info);
	return (info);
}
