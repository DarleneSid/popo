/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsydelny <dsydelny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:33 by dsydelny          #+#    #+#             */
/*   Updated: 2023/08/29 23:21:02 by dsydelny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct t_data
{
	int					nb_philo;
	int					t_t_die;
	int					t_t_sleep;
	int					t_t_eat;
	int					max_eat;
	int					need_to_eat;
	int					death;
	long int			set_to_zero;
	struct t_philo		*philo;
	pthread_mutex_t		print;
	pthread_mutex_t		deathchecker;
	pthread_mutex_t		eatchecker;
	pthread_mutex_t		*spoon;
	pthread_t			*phils;
	pthread_t			watcher;
	pthread_t			*check_time;
}				t_data;

typedef struct t_philo
{
	int					id;
	int					eaten;
	long int			last_lunch;
	pthread_mutex_t		lunchchecker;
	pthread_mutex_t		*l_spoon;
	pthread_mutex_t		*r_spoon;
	t_data				*data;
}				t_philo;

/*		PARSING		*/
int				len_arg(char *s);
int				check_valid_args(char **av);
long long int	ft_atoi(char *n);
int				check_amount_ph(int ac, char **av);
void			*just_one_philo(void *arg);

/*		PHILO		*/
int				lets_malloc(t_data *data, t_philo *philo);
void			init_philos(t_data *data, t_philo *philo);
void			init_mutex(t_data *data);
int				create_thread(t_data *data, t_philo *philo);
int				main(int ac, char **av);

/*		FORKS		*/
void			*print_msg(t_philo *philo, char *str);
void			*die_right_fork(t_philo	*philo);
void			*right_fork(t_philo *philo);
void			*die_left_fork(t_philo	*philo);
void			*left_fork(t_philo	*philo);

/*		PROCESS		*/
void			*food_check(t_data *data, int i);
void			*case_death(t_data *data);
void			*check_time_pass(void *arg);
void			*death_check(t_philo *philo);
void			*process_func(void *arg);

/*		TIME		*/
long int		gettodaystime(void);
int				sleeper(t_philo *philo, long duration, long start);
int				my_usleep(long int duration, t_philo *philo);
void			*setting_time(void *arg);
void			init(t_data *data, char **av, int ac);

void			*ft_calloc(size_t count, size_t size);
void			*print_death(t_data *data, int i);
void			*super_free(t_data *data);

#endif
