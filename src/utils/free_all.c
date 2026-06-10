/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:53:53 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/10 11:45:01 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_table(t_table *table);

void	free_infos(t_infos *infos);

void	free_all(t_moder *moder)
{
	free_table(moder->tables);
	free(moder->tables);
	free_infos(moder->infos);
	free(moder->infos);
	pthread_mutex_destroy(&moder->sim.lock);
	pthread_cond_destroy(&moder->sim.cond);
	free(moder);
}

void	free_table(t_table *table)
{
	int	id;

	id = table->table_id;
	while (table->table_id != id)
	{
		table = table->next;
		pthread_mutex_destroy(&table->coder.lock);
		pthread_mutex_destroy(&table->dongle.lock);
		pthread_mutex_destroy(&table->right_dongle->lock);
	}
}

void	free_infos(t_infos *infos)
{
	pthread_mutex_destroy(&infos->lock);
	pthread_mutex_destroy(&infos->moder_lock);
	pthread_cond_destroy(&infos->cond);
	pthread_cond_destroy(&infos->moder_cond);
	free(infos->ids);
}
