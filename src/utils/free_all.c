/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:53:53 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/09 14:15:24 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void free_table(t_table *table);

void free_infos(t_infos *infos);

void free_all(t_moder *moder)
{
	free_table(moder->tables);
	free_infos(moder->infos);
	free(moder->infos);
	pthread_mutex_destroy(&moder->sim.lock);
	pthread_cond_destroy(&moder->sim.cond);
	free(moder);
	exit(1);
}

void free_table(t_table *table)
{
	t_table *tmp;

	table->prev->next = NULL;
	table->prev = NULL;
	tmp = table;
	while (table->next)
	{
		tmp = table->next;
		pthread_mutex_destroy(&table->coder.lock);
		pthread_mutex_destroy(&table->dongle.lock);
		pthread_mutex_destroy(&table->right_dongle->lock);
		free(table);
		table = tmp;
	}
	free(table);
}

void free_infos(t_infos *infos)
{
	pthread_mutex_destroy(&infos->lock);
	pthread_mutex_destroy(&infos->moder_lock);
	pthread_cond_destroy(&infos->cond);
	pthread_cond_destroy(&infos->moder_cond);
	free(infos->ids);
}
