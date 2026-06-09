/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_burnout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:06:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/09 15:42:41 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void check_burnout_aux(t_moder *moder, t_table *table);

void *check_burnout(void	*arg)
{
	t_moder *moder;
	t_table *table;

	moder = (t_moder*)arg;
	pthread_mutex_lock(&moder->sim.lock);
	while (!moder->sim.continue_sim)
		pthread_cond_wait(&moder->sim.cond, &moder->sim.lock);
	pthread_mutex_unlock(&moder->sim.lock);
	table = moder->tables;
	while (moder->sim.continue_sim)
	{
		pthread_mutex_lock(&table->coder.lock);
		if ((get_time() - table->coder.last_compile >=
			table->coder.time_to_burnout && table->coder.last_compile) ||
			(get_time() - table->sim->start >= table->coder.time_to_burnout &&
			table->sim->start && !table->coder.last_compile))
		{
			check_burnout_aux(moder, table);
			return (NULL);
		}
		pthread_mutex_unlock(&table->coder.lock);
		table = table->next;
		usleep(1);
	}
	return (NULL);
}

void check_burnout_aux(t_moder *moder, t_table *table)
{
	pthread_mutex_unlock(&table->coder.lock);
	moder->sim.continue_sim = 0;
	pthread_cond_broadcast(&moder->infos->moder_cond);
	printf("[%zu] C%d \033[38;2;200;50;50mBURNOUT\033[0m\n",
		get_time() - table->sim->start,table->table_id);
	pthread_join(moder->thread, NULL);
	printf("aqui no final 2\n");
	//free_all(moder);
}
