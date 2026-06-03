/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:13:05 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/03 11:09:18 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void fifo(t_moder *moder)
{
	int id;
	size_t i;

	id = moder->infos->last_id;
	i = 0;
	while (i < moder->infos->list_size)
	{
		printf("id %d\n\n", id);
		moder->infos->ids[i] = id;
		id = (id + moder->nb_coders / 2) % moder->nb_coders;
		i++;
	}
	moder->infos->last_id = id;
}
