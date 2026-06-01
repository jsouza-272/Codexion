/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:14:12 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/01 14:38:59 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int id_in_ids(int id, int *ids, size_t limit)
{
	size_t i;

	i = 0;
	while (i < limit)
	{
		if (id == ids[i])
			return 1;
		i++;
	}
	return 0;
}