/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:27 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/02 15:19:19 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include "colors.h"

typedef struct s_data
{
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				times_must_eat;
	int				philos_count;
}	t_data;

typedef struct s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*meal_mutex;
	bool			is_dead;
	int				meal_count;
	int				philo_index;
	char			*index;
	long			start;
	long			last_meal;
	t_data			*data;

}	t_philo;

typedef struct s_info
{
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				times_must_eat;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*somebody_die_mutex;
	pthread_mutex_t	*print_mutex;
	bool			somebody_die;
	int				philos_count;
	long			start;
}	t_info;

typedef struct s_mix
{
	t_info			*info;
	t_philo			*philo;
}	t_mix;

//	FT_LIBFT.c
int		ft_strlen(char *str);
char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

//	FT_PUTNBR_FD.C
void	ft_putnbr_fd(int n, int fd);

// FT_PRINT_UTILS.c
void	ft_debuglog_thread(t_philo	*philo, char *msg, char *color);
void	ft_debuglog(char *msg, char *color);

//	FT_TIME.c
// unsigned int	ft_get_time(struct timeval start);
long	get_timestamp(void);
void	ft_usleep(t_philo *philo, long int ms);

//	FT_INIT.c
t_philo	*ft_malloc_philo(t_philo *philo, int philo_index, pthread_mutex_t *pm);
t_info	*ft_malloc_info(t_info *info);
pthread_mutex_t	**ft_malloc_forks(t_info *info);
void	ft_assign_forks(t_info *info);
t_info	*ft_parse_info(t_info *info, pthread_mutex_t *pm, char *argv[]);

//	FT_PHILO.c
void	ft_eat(t_philo *philo, t_mix *mix);
void	ft_think(t_philo *philo, t_info *info);
void	ft_sleep(t_philo *philo, t_info *info);
bool	is_dead(t_philo *philo, t_info *info);
void	ft_philo_died(t_philo *philo);
void	ft_print_status(t_philo *philo, t_info *info, char *msg, char *color);

//	FT_DEATH.c
void	*death_routine(void *v);

//	FT_FORKS.c
void	ft_take_forks(t_philo *philo, t_mix *mix);

//	FT_MEALS.c
long	ft_get_last_meal(t_philo *philo);
long	ft_get_previous_last_meal(int current, t_info *info);
long	ft_get_next_last_meal(int current, t_info *info);

#endif
