/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:19:10 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 23:20:47 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lets_malloc(t_data *data, t_philo *philo)
{
	data->phils = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->phils)
		return (free(philo), 1);
	data->check_time = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->check_time)
		return (free(philo), free(data->phils), 1);
	data->spoon = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->spoon)
		return (free(philo), free(data->phils), free(data->check_time), 1);
	data->set_to_zero = gettodaystime();
	data->philo = philo;
	return (0);
}

void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].data = data;
		pthread_mutex_init(&philo[i].lunchchecker, NULL);
		philo[i].l_spoon = &(data->spoon[i]);
		if (philo[i].id == data->nb_philo)
			philo[i].r_spoon = &(data->spoon[0]);
		else
			philo[i].r_spoon = &(data->spoon[i + 1]);
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_init(&data->spoon[i++], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->deathchecker, NULL);
	pthread_mutex_init(&data->eatchecker, NULL);
}

int	create_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->phils[i], NULL, &process_func, &philo[i]))
			return (perror("CREATION OF THREAD FAILED\n"), 1);
		i++;
	}
	i = 0;
	if (pthread_create(&data->watcher, NULL, &check_time_pass, data))
		return (perror("CREATION OF THREAD FAILED\n"), 1);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->phils[i], NULL))
			return (perror("CREATION OF THREAD FAILED\n"), 1);
		i++;
	}
	if (pthread_join(data->watcher, NULL))
		return (perror("CREATION OF THREAD FAILED\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	static t_data	data = {0};
	t_philo			*philo;

	if (ac < 5 || ac > 6)
		return (printf("NOT VALID AMOUNT OF ARGUMENTS\n"), 1);
	if (check_valid_args(av) || check_amount_ph(ac, av))
		exit(1);
	data.nb_philo = ft_atoi(av[1]);
	philo = ft_calloc(sizeof(t_philo), data.nb_philo);
	if (!philo)
		return (1);
	if (lets_malloc(&data, philo))
		return (1);
	init(&data, av, ac);
	init_mutex(&data);
	init_philos(&data, philo);
	if (data.nb_philo == 1)
		return (just_one_philo(philo), super_free(&data), 1);
	create_thread(&data, philo);
	free(data.philo);
	free(data.spoon);
	free(data.phils);
	free(data.check_time);
}
