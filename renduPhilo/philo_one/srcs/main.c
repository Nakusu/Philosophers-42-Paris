/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:27:20 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_eat(t_philo *philo)
{
	int			i;
	t_global	*global;

	global = philo->global;
	i = (philo->id == 0) ? global->nb_philos - 1 : -1;
	if (pthread_mutex_lock(&global->keys[philo->id + i]) == 0)
	{
		ft_messages(philo, "has taken a fork");
		pthread_mutex_lock(&global->keys[philo->id]);
		pthread_mutex_lock(&philo->lock);
		philo->last_meal = ft_get_time(0);
		philo->eat += 1;
		if (philo->eat == global->nb_max_meals && global->nb_max_meals != -1)
			global->eats += 1;
		if (global->eats == global->nb_philos)
			global->die += 1;
		ft_messages2(philo, "is eating");
		ft_usleep(global->time_to_eat);
		pthread_mutex_unlock(&global->keys[philo->id]);
		pthread_mutex_unlock(&global->keys[philo->id + i]);
		pthread_mutex_unlock(&philo->lock);
	}
}

void	ft_sleep(t_philo *philo)
{
	ft_messages(philo, "is sleeping");
	ft_usleep(philo->global->time_to_sleep);
}

void	*ft_actions(void *args)
{
	t_global	*global;
	t_philo		*philo;
	pthread_t	t_monitoring;

	philo = (t_philo *)args;
	global = philo->global;
	if (pthread_create(&t_monitoring, NULL, monitoring, args) != 0)
		return (global);
	pthread_detach(t_monitoring);
	philo->last_meal = ft_get_time(0);
	while (global->die == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_messages(philo, "is thinking");
	}
	return (global);
}

void	ft_core(t_global *global)
{
	int			i;
	pthread_t	tid;

	i = -1;
	while (++i < global->nb_philos)
	{
		if (pthread_create(&tid, NULL, ft_actions, &global->philos[i]) != 0)
			return ;
		pthread_detach(tid);
		ft_usleep(1);
	}
}

int		main(int ac, char **av)
{
	t_global global;

	if (ac == 5 || ac == 6)
	{
		if (ft_init_gbl(av, ac, &global) == 0)
			return (0);
		ft_core(&global);
		ft_global_monitoring(&global);
		ft_free_all(&global);
		return (1);
	}
	ft_putstr("Error : The program hasn't been launched correctly.\n", 2);
	return (1);
}