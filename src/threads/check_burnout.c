/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_burnout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:06:36 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/10 14:08:17 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

int		check_burnout_aux(t_moder *moder, t_table *table);

void	wait_start(t_moder *moder);

void	*check_burnout(void *arg)
{
	t_moder	*moder;
	t_table	*table;

	moder = (t_moder *)arg;
	wait_start(moder);
	table = moder->tables;
	while (moder->sim.continue_sim)
	{
		pthread_mutex_lock(&table->coder.lock);
		if ((get_time()
				- table->coder.last_compile >= table->coder.time_to_burnout
				&& table->coder.last_compile) || (get_time()
				- table->sim->start >= table->coder.time_to_burnout
				&& table->sim->start && !table->coder.last_compile))
		{
			if (check_burnout_aux(moder, table))
				break ;
		}
		pthread_mutex_unlock(&table->coder.lock);
		table = table->next;
		usleep(1000);
	}
	pthread_join(moder->thread, NULL);
	return (NULL);
}

int	check_burnout_aux(t_moder *moder, t_table *table)
{
	if ((get_time() - table->coder.last_compile >= table->coder.time_to_burnout
			&& table->coder.last_compile) || (get_time()
			- table->sim->start >= table->coder.time_to_burnout
			&& table->sim->start && !table->coder.last_compile))
	{
		moder->sim.continue_sim = 0;
		pthread_cond_broadcast(&moder->infos->moder_cond);
		printf("[%zu] C%d \033[38;2;200;50;50mburned out\033[0m\n", get_time()
			- table->sim->start, table->table_id);
		pthread_mutex_unlock(&table->coder.lock);
		return (1);
	}
	return (0);
}

void	wait_start(t_moder *moder)
{
	pthread_mutex_lock(&moder->sim.lock);
	while (!moder->sim.continue_sim)
		pthread_cond_wait(&moder->sim.cond, &moder->sim.lock);
	pthread_mutex_unlock(&moder->sim.lock);
}
