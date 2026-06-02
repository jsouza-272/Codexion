/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:13:05 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/02 12:12:44 by jsouza           ###   ########.fr       */
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
		moder->infos->ids[i] = id + 1;
		id = (id + moder->nb_coders / 2) % moder->nb_coders;
		i++;
	}
	moder->infos->last_id = id;
}
