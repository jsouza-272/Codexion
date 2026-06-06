/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:03:13 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/06 12:03:05 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	parser_error(int error_id)
{
	if (error_id == 0)
		fprintf(stderr, "Usage: ./codexion <number_of_coders> %s%s%s%s",
			"<time_to_burnout> <time_to_compile> ",
			"<time_to_debug> <time_to_refactor> ",
			"<number_of_compiles_required> <dongle_cooldown>",
			" <scheduler>\n");
	else if (error_id == 1)
		fprintf(stderr, "Error: number_of_coders must be at least 1\n");
	else if (error_id == 2)
		fprintf(stderr, "Error: time_to_burnout must be at least 1\n");
	else if (error_id == 3)
		fprintf(stderr, "Error: time_to_compile must be at least 1\n");
	else if (error_id == 4)
		fprintf(stderr, "Error: time_to_debug must be at least 1\n");
	else if (error_id == 5)
		fprintf(stderr, "Error: time_to_refactor must be at least 1\n");
	else if (error_id == 6)
		fprintf(stderr, "Error: number_of_compiles_required must be \
			 at least 1\n");
	else if (error_id == 7)
		fprintf(stderr, "Error: dongle_cooldown must be at least 1\n");
	else if (error_id == 8)
		fprintf(stderr, "Error: value must be either \"fifo\" or \"edf\".\n");
	exit(1);
}

void	error(int error_id, t_table *table, t_infos *infos)
{
	(void)table;
	(void)infos;
	if (0 <= error_id && error_id <= 8)
		parser_error(error_id);
	exit(1);
}
