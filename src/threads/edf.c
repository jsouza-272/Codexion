/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:58:52 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/05 14:37:50 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int select_edf_candidate(t_table *table, t_infos *infos, int nb_coders,
	size_t min, int id);

void	edf(t_moder *moder)
{
	size_t 	i;

	i = 0;
	while (i < moder->infos->list_size)
	{
		moder->infos->ids[i] = select_edf_candidate(moder->tables, moder->infos,
			moder->nb_coders, SIZE_MAX, 1);
		i++;
	}
}

int select_edf_candidate(t_table *table, t_infos *infos, int nb_coders,
	size_t min, int id)
{
	int	j;

	j = 0;
	(void)infos;
	while (j < nb_coders + 1)
	{
		j++;
		table = table->next;
		if (id_in_ids(table->table_id, infos->ids, infos->list_size) ||
			id_in_ids(table->table_id + 1, infos->ids, infos->list_size) ||
			id_in_ids(table->table_id - 1, infos->ids, infos->list_size))
			continue;
		if (table->coder.last_compile < min)
		{
			min = table->coder.last_compile;
			id = table->table_id;
		}
		else if (table->coder.last_compile == min && id > table->table_id)
		{
			min = table->coder.last_compile;
			id = table->table_id;
		}
	}
	return (id);
}
