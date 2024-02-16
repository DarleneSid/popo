/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:22:57 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 20:45:03 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	gettodaystime(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) == -1)
		return (-1);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

int	sleeper(t_philo *philo, long duration, long start)
{
	int	current;

	while (1)
	{
		current = gettodaystime() - start;
		if (current >= duration)
			break ;
		if (duration - current > 1000)
			usleep(100);
		else
			usleep((duration - current) / 10);
		pthread_mutex_lock(&philo->data->deathchecker);
		if (philo->data->death == 0)
		{
			pthread_mutex_unlock(&philo->data->deathchecker);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->deathchecker);
	}
	return (0);
}

int	my_usleep(long int duration, t_philo *philo)
{
	long int	start;

	(void)philo;
	start = gettodaystime();
	if (start == -1)
		return (1);
	else if (sleeper(philo, duration, start))
		return (1);
	return (0);
}

void	*setting_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("[%ld] %i\n", gettodaystime() - philo->data->set_to_zero,
			philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	return (0);
}

void	init(t_data *data, char **av, int ac)
{
	data->t_t_die = ft_atoi(av[2]);
	data->t_t_sleep = ft_atoi(av[4]);
	data->t_t_eat = ft_atoi(av[3]);
	data->max_eat = -1;
	data->need_to_eat = -1;
	if (ac == 6)
	{
		data->max_eat = ft_atoi(av[5]);
		data->need_to_eat = data->nb_philo * data->max_eat;
	}
	data->death = 1;
}
