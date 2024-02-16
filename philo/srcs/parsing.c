/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:21:08 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 23:21:52 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	len_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_valid_args(char **av)
{
	int	n_av;
	int	is_av;

	n_av = 1;
	if (!av)
		return (1);
	while (av[n_av])
	{
		if (len_arg(av[n_av]) == 0)
			return (write (1, "EMPTY ARGUMENT\n", 16), 1);
		is_av = 0;
		while (av[n_av][is_av])
		{
			if (!(av[n_av][is_av] >= '0' && av[n_av][is_av] <= '9'))
			{
				printf("NOT VALID ARGUMENT: %s\n", av[n_av]);
				return (1);
			}
			is_av++;
		}
		n_av++;
	}
	return (0);
}

long long int	ft_atoi(char *n)
{
	long long int	res;
	int				i;

	res = 0;
	i = 0;
	if (n[i] == ' ' || (n[i] >= 9 && n[i] <= 13))
		i++;
	while (n[i] >= '0' && n[i] <= '9')
	{
		res = res * 10 + n[i] - '0';
		if (res > 2147483647)
			return (write (2, "NUMBER IS TOO BIG\n", 18), -1);
		i++;
	}
	return (res);
}

int	check_amount_ph(int ac, char **av)
{
	int	i;
	int	val;

	i = 2;
	val = ft_atoi(av[1]);
	if (val == -1)
		return (1);
	if (val > 200)
	{
		printf("MAX AMOUNT OF PHILOS IS 200, YOU PUT %s\n", av[1]);
		return (1);
	}
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	*just_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_msg(philo, "taken a fork");
	my_usleep(philo->data->t_t_die, philo);
	print_msg(philo, "died");
	return (NULL);
}
