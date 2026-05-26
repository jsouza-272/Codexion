/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:35:48 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/26 13:53:22 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_table	*init(t_config c)
{
	t_table	*tables;
	size_t	i;

	tables = malloc(c.number_of_coders * sizeof(t_table));
	if (!tables)
		error(9);
	i = 0;
	while (i < c.number_of_coders)
	{
		create_table(&tables[i], tables, c, i);
		i++;
	}
	return tables;
}

void	create_table(t_table	*table, t_table	*tables,
	t_config	c, size_t	i)
{
	create_coder(&table->coder, c);
	create_dongle(&table->dongle, c);
	table->right_table = &tables[(i + 1) % c.number_of_coders];
	table->left_table = &tables[(i + c.number_of_coders - 1)
		% c.number_of_coders];
}

void	create_dongle(t_dongle	*dongle, t_config	c)
{
	dongle->last_use = 0;
	dongle->dongle_cooldown = c.dongle_cooldown;
}

void	create_coder(t_coder	*coder, t_config	c)
{
	coder->last_compile = 0;
	coder->time_to_burnout = c.time_to_burnout;
	coder->time_to_compile = c.time_to_compile;
	coder->time_to_debug = c.time_to_debug;
	coder->time_to_refactor = c.time_to_refactor;
	pthread_create(&coder->thread, NULL);
}
