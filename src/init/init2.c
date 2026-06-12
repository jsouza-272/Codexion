/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:28:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/12 10:30:08 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

t_infos	*init_infos(t_config c, t_table *table, t_moder *moder)
{
	t_infos	*infos;

	infos = ft_calloc(1, sizeof(t_infos));
	if (!infos)
		error(11, table, NULL, moder);
	infos->ids = ft_calloc(c.number_of_coders / 2, sizeof(int));
	if (!infos->ids)
		error(12, table, infos, moder);
	infos->list_size = c.number_of_coders / 2;
	pthread_cond_init(&infos->cond, NULL);
	pthread_mutex_init(&infos->lock, NULL);
	pthread_cond_init(&infos->moder_cond, NULL);
	pthread_mutex_init(&infos->moder_lock, NULL);
	return (infos);
}
