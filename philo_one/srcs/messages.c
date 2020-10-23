/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:27:08 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

char	*ft_construct_str(char *str, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	str[i++] = ' ';
	while (src[j])
		str[i++] = src[j++];
	str[i++] = '\n';
	str[i] = 0;
	return (str);
}

char	*ft_construct_nbr(char *str, char *nb1, char *nb2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ft_strlen(nb1))
		str[j++] = nb1[i++];
	i = 0;
	str[j++] = ' ';
	while (i < ft_strlen(nb2))
		str[j++] = nb2[i++];
	str[j] = 0;
	return (str);
}

void	ft_print_msg(t_philo *philo, char *message)
{
	char	tmp[50];
	char	tmpnbr[50];
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(ft_get_time(philo->global->t_start));
	tmp2 = ft_itoa(philo->id);
	ft_construct_nbr(tmpnbr, tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	ft_putstr(tmpnbr, 1);
	ft_putstr(ft_construct_str(tmp, message), 1);
}

void	ft_messages(t_philo *philo, char *message)
{
	if (pthread_mutex_lock(&philo->global->talk) == 0)
		ft_print_msg(philo, message);
	pthread_mutex_unlock(&philo->global->talk);
}

void	ft_messages2(t_philo *philo, char *message)
{
	if (pthread_mutex_lock(&philo->global->talk) == 0)
	{
		ft_print_msg(philo, "has taken a fork");
		ft_print_msg(philo, message);
	}
	if (philo->global->die == 0)
		pthread_mutex_unlock(&philo->global->talk);
}