/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:21:27 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 14:57:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include "colors.h"

typedef struct s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	int				philo_index;
	char			*index;
}	t_philo;

typedef struct s_info
{
	int				time_eat;
	int				time_think;
	int				time_die;
	t_philo			**philos;
	struct timeval	start;
}	t_info;


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
unsigned int	ft_get_time(t_info *info);

#endif
