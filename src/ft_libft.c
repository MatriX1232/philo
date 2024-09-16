/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:26:16 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/16 14:01:04 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory_block;
	size_t	i;

	if (nmemb >= 4294967295 || size >= 4294967295)
	{
		if (size != 0 && nmemb != 0)
			return (NULL);
	}
	memory_block = malloc(nmemb * size);
	if (memory_block == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		*(char *)(memory_block + i) = 0;
		i++;
	}
	return (memory_block);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	str = (char *)ft_calloc((len1 + len2 + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (i++ < len1)
		str[i] = (char)s1[i];
	i = -1;
	while (i++ < len2)
		str[len1 + i] = (char)s2[i];
	return (str);
}
