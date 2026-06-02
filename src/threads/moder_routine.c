/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:36:43 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/02 11:00:38 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void join_all_threads(t_moder *moder);

void *moder_routine(void *arg)
{
	t_moder *moder;

	moder = (t_moder*)arg;
	while(moder->nbcr > moder->current_compiles)
	{
		// printf("MODER DOING\n\n");
		pthread_mutex_lock(&moder->infos->lock);
		if (moder->scheduler == FIFO)
			fifo(moder);
		else
			edf(moder);
		pthread_mutex_unlock(&moder->infos->lock);
		// printf("%d %d\n", moder->infos->ids[0], moder->infos->ids[1]);
		pthread_cond_broadcast(&moder->infos->cond);
	}
	moder->simulation.continue_sim = 0;
	join_all_threads(moder);
	return (NULL);
}

void join_all_threads(t_moder *moder)
{
	t_table *table;
	int id;

	table = moder->tables;
	id = table->table_id;
	pthread_join(table->coder.thread, NULL);
	table = table->next;
	while (table->table_id != id)
	{
		pthread_join(table->coder.thread, NULL);
		table = table->next;
	}
}
