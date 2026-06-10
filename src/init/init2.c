/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:28:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/10 11:50:20 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_infos	*init_infos(t_config c)
{
	t_infos	*infos;

	infos = ft_calloc(1, sizeof(t_infos));
	if (!infos)
		error(11, NULL, NULL);
	infos->ids = ft_calloc(c.number_of_coders / 2, sizeof(int));
	if (!infos->ids)
		error(12, NULL, infos);
	infos->list_size = c.number_of_coders / 2;
	pthread_cond_init(&infos->cond, NULL);
	pthread_mutex_init(&infos->lock, NULL);
	pthread_cond_init(&infos->moder_cond, NULL);
	pthread_mutex_init(&infos->moder_lock, NULL);
	return (infos);
}
