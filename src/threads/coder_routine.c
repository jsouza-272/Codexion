/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:04:11 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/09 10:28:38 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void compile(t_dongle *d1, t_dongle *d2, t_coder *coder, int id);

void debug(t_coder *coder, int id);

void refactor(t_coder *coder, int id);

void coder_routine_aux(t_table *table);

void *coder_routine(void *arg)
{
	t_table *table;

	table = (t_table*)arg;
	pthread_mutex_lock(&table->sim->lock);
	while (!table->sim->continue_sim)
		pthread_cond_wait(&table->sim->cond, &table->sim->lock);
	pthread_mutex_unlock(&table->sim->lock);
	if (!table->coder.last_compile)
		table->coder.last_compile = get_time();
	table->coder.start = get_time();
	while (table->sim->continue_sim)
	{
		pthread_mutex_lock(&table->infos->lock);
		while (!id_in_ids(table->table_id, table->infos->ids,
			table->infos->list_size) && table->sim->continue_sim)
			pthread_cond_wait(&table->infos->cond, &table->infos->lock);
		pthread_mutex_unlock(&table->infos->lock);
		if (!table->sim->continue_sim)
			break;
		coder_routine_aux(table);
	}
	return (NULL);
}

void coder_routine_aux(t_table *table)
{
	compile(&table->dongle, table->right_dongle,
			&table->coder, table->table_id);
	pthread_mutex_lock(&table->infos->moder_lock);
	table->infos->counter += 1;
	pthread_mutex_unlock(&table->infos->moder_lock);
	pthread_cond_broadcast(&table->infos->moder_cond);
	debug(&table->coder, table->table_id);
	refactor(&table->coder, table->table_id);
}

void compile(t_dongle *d1, t_dongle *d2, t_coder *coder, int id)
{
	while (get_time() - d1->last_use < d1->dongle_cooldown ||
		   get_time() - d2->last_use < d2->dongle_cooldown)
		usleep(1);
	pthread_mutex_lock(&d1->lock);
	pthread_mutex_lock(&d2->lock);
	printf("[%zu] C%d  has taken a dongle\n", get_time() - coder->start, id);
	printf("[%zu] C%d  has taken a dongle\n", get_time() - coder->start, id);
	printf("[%zu] C%d COMPILE\n", get_time() - coder->start, id);
	usleep(coder->time_to_compile * 1000);
	pthread_mutex_lock(&coder->lock);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->lock);
	d1->last_use = get_time();
	d2->last_use = get_time();
	pthread_mutex_unlock(&d1->lock);
	pthread_mutex_unlock(&d2->lock);
}

void debug(t_coder *coder, int id)
{
	printf("[%zu] C%d DEBUG\n", get_time() - coder->start, id);
	fflush(stdout);
	usleep(coder->time_to_debug * 1000);
}

void refactor(t_coder *coder, int id)
{
	printf("[%zu] C%d REFACTOR\n", get_time() - coder->start, id);
	fflush(stdout);
	usleep(coder->time_to_refactor * 1000);
}
