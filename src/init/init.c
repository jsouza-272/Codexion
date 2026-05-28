/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:48 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/28 11:50:20 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

t_table	*init(t_config c)
{
	t_table	*tables;
	t_infos *infos;
	size_t	i;

	tables = malloc(c.number_of_coders * sizeof(t_table));
	if (!tables)
		error(9, NULL, NULL);
	infos = malloc(sizeof(t_infos));
	if (!infos)
		error(10, tables, NULL);
	infos->ids = malloc(sizeof(int) * (c.number_of_coders / 2));
	if (!infos->ids)
		error(11, infos, tables);
	infos->list_size = c.number_of_coders / 2;
	pthread_cond_init(&infos->cond, NULL);
	pthread_mutex_init(&infos->lock, NULL);
	i = 0;
	while (i < c.number_of_coders)
	{
		create_table(&tables[i], tables, c, i);
		tables[i].infos = infos;
		i++;
	}
	return tables;
}

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i)
{
	create_coder(&table->coder, c, &table);
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
