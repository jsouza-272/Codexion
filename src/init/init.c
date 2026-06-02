/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:48 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/02 10:37:57 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i);

void	create_dongle(t_dongle	*dongle, t_config	c);

void	create_coder(t_coder	*coder, t_config	c, t_table	*table);

t_table	*init_tables(t_config c, t_moder *moder);

t_moder *init(t_config c)
{
	t_moder *moder;

	moder = malloc(sizeof(t_moder));
	if (!moder)
		error(9, NULL, NULL);
	printf("MODER CREATED\n\n");
	moder->simulation.continue_sim = 1;
	// printf("HERE\n\n");
	moder->nb_coders = c.number_of_coders;
	moder->nbcr = c.number_of_compiles_required * c.number_of_coders;
	moder->scheduler = c.scheduler;
	moder->current_compiles = 0;
	moder->tables = init_tables(c, moder);
	moder->infos = moder->tables->infos;
	printf("TABLES CREATED\n\n");
	pthread_create(&moder->thread, NULL, &moder_routine, moder);
	return (moder);
}

t_table	*init_tables(t_config c, t_moder *moder)
{
	t_table	*tables;
	t_infos *infos;
	int	i;

	tables = malloc(c.number_of_coders * sizeof(t_table));
	if (!tables)
		error(10, NULL, NULL);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		error(11, tables, NULL);
	infos->ids = malloc(sizeof(int) * (c.number_of_coders / 2));
	if (!infos->ids)
		error(12, tables, infos);
	infos->list_size = c.number_of_coders / 2;
	pthread_cond_init(&infos->cond, NULL);
	pthread_mutex_init(&infos->lock, NULL);
	i = 0;
	while (i < c.number_of_coders)
	{
		create_table(&tables[i], tables, c, i);
		tables[i].infos = infos;
		tables[i].sim = &moder->simulation;
		i++;
	}
	return tables;
}

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i)
{
	create_coder(&table->coder, c, table);
	create_dongle(&table->dongle, c);
	table->table_id = i;
	table->next = &tables[(i + 1) % c.number_of_coders];
	table->prev = &tables[(i + c.number_of_coders - 1)
		% c.number_of_coders];
	table->right_dongle = &tables[(i + 1) % c.number_of_coders].dongle;
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
	pthread_create(&coder->thread, NULL, &coder_routine, table);
}
