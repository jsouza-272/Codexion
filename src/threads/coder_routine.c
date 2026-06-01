/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:04:11 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/01 14:40:52 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void compile(t_dongle *d1, t_dongle *d2, t_coder *coder);

void debug(t_coder *coder);

void refactor(t_coder *coder);

void *coder_routine(void *arg)
{
	t_table *table;

	table = (t_table*)arg;
	while (table->sim)
	{
		pthread_mutex_lock(&table->infos->lock);
		while (!id_in_ids(table->table_id, table->infos->ids,
			table->infos->list_size))
			pthread_cond_wait(&table->infos->cond, &table->infos->lock);
		pthread_mutex_unlock(&table->infos->lock);
		compile(&table->dongle, table->right_dongle, &table->coder);
		debug(&table->coder);
		refactor(&table->coder);
	}
	return (NULL);
}
void compile(t_dongle *d1, t_dongle *d2, t_coder *coder)
{
	pthread_mutex_lock(&d1->lock);
	pthread_mutex_lock(&d2->lock);
	usleep(coder->time_to_compile * 1000);
	coder->last_compile = get_time();
	d1->last_use = get_time();
	d2->last_use = get_time();
	pthread_mutex_unlock(&d1->lock);
	pthread_mutex_unlock(&d2->lock);
}

void debug(t_coder *coder)
{
	usleep(coder->time_to_debug * 1000);
}

void refactor(t_coder *coder)
{
	usleep(coder->time_to_refactor * 1000);
}
