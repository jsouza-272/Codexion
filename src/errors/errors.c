/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:03:13 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/28 11:49:46 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

void	parser_error(int error_id)
{
	if (error_id == 0)
		fprintf(2, "Usage: ./codexion <number_of_coders> <time_to_burnout> "
				"<time_to_compile> <time_to_debug> <time_to_refactor> "
				"<number_of_compiles_required> <dongle_cooldown>"
				" <scheduler>\n");
	else if (error_id == 1)
		fprintf(2, "Error: number_of_coders must be at least 1\n");
	else if (error_id == 2)
		fprintf(2, "Error: time_to_burnout must be at least 1\n");
	else if (error_id == 3)
		fprintf(2, "Error: time_to_compile must be at least 1\n");
	else if (error_id == 4)
		fprintf(2, "Error: time_to_debug must be at least 1\n");
	else if (error_id == 5)
		fprintf(2, "Error: time_to_refactor must be at least 1\n");
	else if (error_id == 6)
		fprintf(2, "Error: number_of_compiles_required must be at least 1\n");
	else if (error_id == 7)
		fprintf(2, "Error: dongle_cooldown must be at least 1\n");
	else if (error_id == 8)
		fprintf(2, "Error: value must be either \"fifo\" or \"edf\".\n");
	exit(1);
}

void	error(int error_id, t_table *table, t_infos *infos)
{
	if (0 <= error_id && error_id <= 8)
		parser_error(error_id);
}
