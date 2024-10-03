/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:42:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/04 00:02:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_atoi_args(t_info *info, char *argv[], int *philo_count)
{
	*philo_count = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
}

static bool	ft_adata(t_philo **philo, t_info *info, pthread_mutex_t *pm, int i)
{
	*philo = ft_malloc_philo(*philo, i, pm);
	if (philo == NULL)
		return (ft_debuglog("Problem with philo malloc\n", RED), false);
	(*philo)->start = info->start;
	(*philo)->last_meal = 0;
	(*philo)->data->philos_count = info->philos_count;
	(*philo)->data->time_die = info->time_die;
	(*philo)->data->time_eat = info->time_eat;
	(*philo)->data->times_must_eat = info->times_must_eat;
	(*philo)->data->time_sleep = info->time_sleep;
	return (true);
}

static bool	ft_check_arg_vaidity(t_info *info, char *argv[], int philo_count)
{
	if (philo_count < 1)
		return (ft_debuglog("Invalid arguments\n", RED), false);
	else if (info->time_die < 1 || info->time_eat < 1 || info->time_sleep < 1)
		return (ft_debuglog("Invalid arguments\n", RED), false);
	else if (argv[5] && info->times_must_eat < 1)
		return (ft_debuglog("Invalid arguments\n", RED), false);
	return (true);
}

t_info	*ft_malloc_info(t_info *info)
{
	size_t	p_mts;

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
	p_mts = sizeof(pthread_mutex_t);
	info->somebody_die_mutex = (pthread_mutex_t *) malloc(1 * p_mts);
	if (!info->somebody_die_mutex)
		return (NULL);
	pthread_mutex_init(info->somebody_die_mutex, NULL);
	info->somebody_die = false;
	return (info);
}

t_info	*ft_parse_info(t_info *info, pthread_mutex_t *pm, char *argv[])
{
	int		philo_count;
	int		i;
	t_philo	**philos;

	ft_atoi_args(info, argv, &philo_count);
	if (ft_check_arg_vaidity(info, argv, philo_count) == false)
		return (ft_free_info(info, NULL, pm), NULL);
	info->philos_count = philo_count;
	info->print_mutex = pm;
	philos = (t_philo **) malloc((philo_count + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	ft_debuglog("Initialized philosopher with number: ", YELLOW);
	i = -1;
	while (++i < philo_count)
	{
		if (!ft_adata(&philos[i], info, pm, i))
			return (NULL);
	}
	write(1, "\n", 1);
	philos[i] = NULL;
	info->philos = philos;
	info->forks = ft_malloc_forks(info);
	ft_assign_forks(info);
	return (info);
}
