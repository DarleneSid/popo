/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:32:19 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 23:22:34 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*s1;

	if (n == 0)
		return ;
	i = 0;
	s1 = (char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	str = (char *)malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return ((void *)str);
}

void	*print_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->print);
	printf("%ld	№%d died\n", gettodaystime() - data->set_to_zero,
		i + 1);
	pthread_mutex_unlock(&data->print);
	return (NULL);
}

void	*super_free(t_data *data)
{
	free(data->philo);
	free(data->spoon);
	free(data->phils);
	free(data->check_time);
	return (NULL);
}
