/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:14:12 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/03 11:17:42 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int id_in_ids(int id, int *ids, size_t limit)
{
	size_t i;

	i = 0;
	if (id == 0)
	printf("\n0000000\n");
	while (i < limit)
	{
		if (id == ids[i])
		return 1;
		i++;
	}
	printf("\n<><<%d\n",id);
	return 0;
}