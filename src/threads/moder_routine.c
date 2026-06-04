/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:36:43 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/04 13:28:16 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void join_all_threads(t_moder *moder);

void *moder_routine(void *arg)
{
	t_moder *moder;

	moder = (t_moder*)arg;
	pthread_mutex_lock(&moder->simulation.lock);
	while (!moder->simulation.continue_sim)
		pthread_cond_wait(&moder->simulation.cond, &moder->simulation.lock);
	pthread_mutex_unlock(&moder->simulation.lock);
	while(moder->nbcr > moder->current_compiles)
	{
		pthread_mutex_lock(&moder->infos->lock);
		if (moder->scheduler == FIFO)
			fifo(moder);
		else
			edf(moder);
		pthread_mutex_unlock(&moder->infos->lock);
		pthread_cond_broadcast(&moder->infos->cond);
		pthread_mutex_lock(&moder->infos->moder_lock);
		while (moder->infos->counter < moder->infos->list_size)
			pthread_cond_wait(&moder->infos->moder_cond, &moder->infos->moder_lock);
		pthread_mutex_unlock(&moder->infos->moder_lock);
		moder->infos->counter = 0;
		moder->current_compiles++;
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
	pthread_cond_broadcast(&moder->infos->cond);
	pthread_join(table->coder.thread, NULL);
	printf("C%d acabou\n", table->table_id);
	table = table->next;
	while (table->table_id != id)
	{
		pthread_join(table->coder.thread, NULL);
		printf("C%d acabou\n", table->table_id);
		table = table->next;
	}
	printf("\nBYE!\n");
}
