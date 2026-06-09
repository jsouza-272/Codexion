/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:48 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/09 14:38:48 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i, t_infos *infos, t_simulation *sim);

void	create_dongle(t_dongle	*dongle, t_config	c);

void	create_coder(t_coder	*coder, t_config	c, t_table	*table);

t_table	*init_tables(t_config c, t_moder *moder);

t_moder *init(t_config c)
{
	t_moder *moder;

	moder = ft_calloc(1, sizeof(t_moder));
	if (!moder)
		error(9, NULL, NULL);
	pthread_cond_init(&moder->sim.cond, NULL);
	pthread_mutex_init(&moder->sim.lock, NULL);
	pthread_create(&moder->thread, NULL, &moder_routine, moder);
	pthread_create(&moder->thread2, NULL, &check_burnout, moder);
	moder->nb_coders = c.number_of_coders;
	moder->nbcr = c.number_of_compiles_required * c.number_of_coders;
	moder->scheduler = c.scheduler;
	moder->current_compiles = 0;
	moder->tables = init_tables(c, moder);
	moder->infos = moder->tables->infos;
	moder->sim.continue_sim = 1;
	moder->sim.moder = moder;
	pthread_cond_broadcast(&moder->sim.cond);
	return (moder);
}

t_table	*init_tables(t_config c, t_moder *moder)
{
	t_table	*tables;
	t_infos *infos;
	int	i;

	tables = ft_calloc(c.number_of_coders, sizeof(t_table));
	if (!tables)
		error(10, NULL, NULL);
	infos = init_infos(c);
	i = 0;
	while (i < c.number_of_coders)
	{
		create_table(&tables[i], tables, c, i, infos, &moder->sim);
		i++;
	}
	return &tables[0];
}

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i, t_infos *infos, t_simulation *sim)
{
	table->table_id = i + 1;
	table->next = &tables[(i + 1) % c.number_of_coders];
	table->prev = &tables[(i + c.number_of_coders - 1)
		% c.number_of_coders];
	table->right_dongle = &tables[(i + 1) % c.number_of_coders].dongle;
	table->infos = infos;
	table->sim = sim;
	create_dongle(&table->dongle, c);
	create_coder(&table->coder, c, table);
}

void	create_dongle(t_dongle	*dongle, t_config	c)
{
	dongle->last_use = 0;
	dongle->dongle_cooldown = c.dongle_cooldown;
	pthread_mutex_init(&dongle->lock, NULL);
}

void	create_coder(t_coder	*coder, t_config	c, t_table	*table)
{
	coder->last_compile = 0;
	coder->time_to_burnout = c.time_to_burnout;
	coder->time_to_compile = c.time_to_compile;
	coder->time_to_debug = c.time_to_debug;
	coder->time_to_refactor = c.time_to_refactor;
	pthread_mutex_init(&coder->lock, NULL);
	pthread_create(&coder->thread, NULL, &coder_routine, table);
}
