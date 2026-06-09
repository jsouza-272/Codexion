/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_burnout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:06:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/09 10:19:02 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void *check_burnout(void	*arg)
{
	t_moder *moder;
	t_table *table;

	moder = (t_moder*)arg;
	pthread_mutex_lock(&moder->simulation.lock);
	while (!moder->simulation.continue_sim)
		pthread_cond_wait(&moder->simulation.cond, &moder->simulation.lock);
	pthread_mutex_unlock(&moder->simulation.lock);
	table = moder->tables;
	while (moder->simulation.continue_sim)
	{
		pthread_mutex_lock(&table->coder.lock);
		if (get_time() - table->coder.last_compile >=
			table->coder.time_to_burnout && table->coder.last_compile)
		{
			printf("[%zu] C%d BURNOUT\n", get_time() - table->coder.start,
			table->table_id);
			exit(1);
		}
		pthread_mutex_unlock(&table->coder.lock);
		table = table->next;
	}
	return (NULL);
}
