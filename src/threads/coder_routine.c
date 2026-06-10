/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:04:11 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/10 12:18:13 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

void	compile(t_dongle *d1, t_dongle *d2, t_table *table, int id);

void	debug(t_table *table, int id, size_t start);

void	refactor(t_table *table, int id, size_t start);

void	coder_routine_aux(t_table *table);

void	*coder_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	pthread_mutex_lock(&table->sim->lock);
	while (!table->sim->continue_sim)
		pthread_cond_wait(&table->sim->cond, &table->sim->lock);
	pthread_mutex_unlock(&table->sim->lock);
	while (table->sim->continue_sim)
	{
		pthread_mutex_lock(&table->infos->lock);
		while (!id_in_ids(table->table_id, table->infos->ids,
				table->infos->list_size) && table->sim->continue_sim)
			pthread_cond_wait(&table->infos->cond, &table->infos->lock);
		pthread_mutex_unlock(&table->infos->lock);
		if (!table->sim->continue_sim)
			break ;
		coder_routine_aux(table);
	}
	return (NULL);
}

void	coder_routine_aux(t_table *table)
{
	pthread_mutex_lock(&table->sim->lock);
	if (!table->sim->continue_sim)
		return ;
	pthread_mutex_unlock(&table->sim->lock);
	compile(&table->dongle, table->right_dongle, table, table->table_id);
	pthread_mutex_lock(&table->infos->moder_lock);
	table->infos->counter += 1;
	pthread_mutex_unlock(&table->infos->moder_lock);
	pthread_cond_broadcast(&table->infos->moder_cond);
	debug(table, table->table_id, table->sim->start);
	refactor(table, table->table_id, table->sim->start);
}

void	compile(t_dongle *d1, t_dongle *d2, t_table *table, int id)
{
	while (get_time() - d1->last_use < d1->dongle_cooldown || get_time()
		- d2->last_use < d2->dongle_cooldown)
	{
		if (!table->sim->continue_sim)
			return ;
		usleep(1);
	}
	pthread_mutex_lock(&d1->lock);
	pthread_mutex_lock(&d2->lock);
	printf("[%zu] C%d  has taken a dongle\n", get_time() - table->sim->start,
		id);
	printf("[%zu] C%d  has taken a dongle\n", get_time() - table->sim->start,
		id);
	printf("[%zu] C%d is compiling\n", get_time() - table->sim->start, id);
	pthread_mutex_lock(&table->coder.lock);
	table->coder.last_compile = get_time();
	pthread_mutex_unlock(&table->coder.lock);
	usleep(table->coder.time_to_compile * 1000);
	d1->last_use = get_time();
	d2->last_use = get_time();
	pthread_mutex_unlock(&d1->lock);
	pthread_mutex_unlock(&d2->lock);
}

void	debug(t_table *table, int id, size_t start)
{
	if (!table->sim->continue_sim)
		return ;
	printf("[%zu] C%d  is debugging\n", get_time() - start, id);
	usleep(table->coder.time_to_compile * 1000);
}

void	refactor(t_table *table, int id, size_t start)
{
	if (!table->sim->continue_sim)
		return ;
	printf("[%zu] C%d is refactoring\n", get_time() - start, id);
	usleep(table->coder.time_to_compile * 1000);
}
