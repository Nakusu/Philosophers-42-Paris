/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 09:27:02 by user42            #+#    #+#             */
/*   Updated: 2020/09/26 16:25:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

sem_t	*launch_sem(char *array, int i)
{
	sem_unlink(array);
	return (sem_open(array, O_CREAT | O_EXCL, 0644, i));
}

void	initphilos(t_global *global)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(global->philos = malloc((sizeof(t_philo) * global->maxthreads))))
	{
		ft_putstr("Error : malloc problem !\n", 2);
		return ;
	}
	while (i < global->maxthreads)
	{
		tmp = ft_itoa(i);
		global->philos[i].id = i;
		global->philos[i].eat = 0;
		global->philos[i].last_eat = 0;
		global->philos[i].global = global;
		global->philos[i].lock = launch_sem(tmp, 1);
		global->philos[i].lockeat = launch_sem(tmp, 0);
		free(tmp);
		i++;
	}
}

int		initgobal(char **str, int ac, t_global *global)
{
	global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
	global->threads = 0;
	global->die = 0;
	global->t_start = get_time(0);
	global->eats = 0;
	if ((ac == 6 && global->maxeats <= 0) ||
	(global->maxthreads = ft_atoi(str[1])) <= 0 ||
	(global->timedie = ft_atoi(str[2])) <= 0 ||
	(global->timeeat = ft_atoi(str[3])) <= 0 ||
	(global->tsleep = ft_atoi(str[4])) <= 0)
	{
		ft_putstr("Error : launch correctly the program !\n", 2);
		return (0);
	}
	initphilos(global);
	global->lock = launch_sem("LOCK", 0);
	global->talk = launch_sem("TALK", 1);
	global->keys = launch_sem("KEYS", global->maxthreads);
	return (1);
}
