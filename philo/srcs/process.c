/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:29 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 20:42:39 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*food_check(t_data *data, int i)
{
	pthread_mutex_lock(&data->eatchecker);
	if (!data->need_to_eat)
	{
		pthread_mutex_unlock(&data->eatchecker);
		case_death(data);
		pthread_mutex_lock(&data->print);
		printf("%ld	№%d died\n", gettodaystime() - data->set_to_zero,
			i + 1);
		pthread_mutex_unlock(&data->print);
		return ("DIED");
	}
	pthread_mutex_unlock(&data->eatchecker);
	return (NULL);
}

void	*case_death(t_data *data)
{
	pthread_mutex_lock(&data->deathchecker);
	data->death = 0;
	pthread_mutex_unlock(&data->deathchecker);
	return (NULL);
}

void	*check_time_pass(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].lunchchecker);
			if (gettodaystime() - data->set_to_zero
				- data->philo[i].last_lunch >= data->t_t_die)
			{
				pthread_mutex_unlock(&data->philo[i].lunchchecker);
				case_death(data);
				print_death(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].lunchchecker);
			if (food_check(data, i))
				return (NULL);
		}
	}
	return (NULL);
}

void	*death_check(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (right_fork(philo))
			return ("DIE");
	}
	else
	{
		if (left_fork(philo))
			return ("DIE");
	}
	return (NULL);
}

void	*process_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		my_usleep(philo->data->t_t_die / 7, philo);
	while (1)
	{
		if ((philo->data->nb_philo % 2 != 0) && philo->eaten > 0)
			usleep(philo->data->t_t_die * 0.25);
		if (death_check(philo))
			return (NULL);
		if (print_msg(philo, "is sleeping"))
			return (NULL);
		if (my_usleep(philo->data->t_t_sleep, philo))
			return (NULL);
		if (print_msg(philo, "is thinking"))
			return (NULL);
	}
	return (NULL);
}
