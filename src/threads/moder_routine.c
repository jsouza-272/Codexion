/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:36:43 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/03 11:20:46 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void join_all_threads(t_moder *moder);

void *moder_routine(void *arg)
{
	t_moder *moder;

	moder = (t_moder*)arg;
	pthread_mutex_lock(&moder->lock);
	while (!moder->simulation.continue_sim)
		pthread_cond_wait(&moder->cond, &moder->lock);
	printf("GO GO GO\n");
	printf("C%d\tC%d\n", moder->tables->table_id, moder->tables->next->table_id);
	fflush(stdout);
	while(moder->nbcr >= moder->current_compiles)
	{
		printf("nbcr: %ld\tcurrent compile: %ld\n", moder->nbcr, moder->current_compiles);
		pthread_mutex_lock(&moder->infos->lock);
		if (moder->scheduler == FIFO)
			fifo(moder);
		else
			edf(moder);
		pthread_mutex_unlock(&moder->infos->lock);
		pthread_cond_broadcast(&moder->infos->cond);
		printf("ACORDA!!!!\n");
		usleep(moder->tables->coder.time_to_compile * 1000);
		moder->current_compiles++;
	}
	moder->simulation.continue_sim = 0;
	pthread_mutex_unlock(&moder->lock);
	printf("\nBYE!\n");
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
	printf("\nBYE!\n");
}
