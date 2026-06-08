/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_burnout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:06:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/08 14:41:13 by jsouza           ###   ########.fr       */
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
		if (get_time() - table->coder.last_compile >=
			table->coder.time_to_burnout && table->coder.last_compile)
		{
			printf("BURNOUT\n");
			exit(1);
		}
		table = table->next;
	}
	return (NULL);
}
