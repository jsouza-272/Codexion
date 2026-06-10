/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:25:22 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/10 15:14:00 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

int	aux_parser(char *value, int error_id)
{
	int	nb;

	nb = atoi(value);
	if (nb <= 0)
		error(error_id, NULL, NULL, NULL);
	return (nb);
}

t_config	parser(int argc, char **argv)
{
	t_config	config;

	if (argc != 9)
		error(0, NULL, NULL, NULL);
	config.number_of_coders = aux_parser(argv[1], 1);
	config.time_to_burnout = aux_parser(argv[2], 2);
	config.time_to_compile = aux_parser(argv[3], 3);
	config.time_to_debug = aux_parser(argv[4], 4);
	config.time_to_refactor = aux_parser(argv[5], 5);
	config.number_of_compiles_required = aux_parser(argv[6], 6);
	config.dongle_cooldown = aux_parser(argv[7], 7);
	if (strcmp(argv[8], "fifo") == 0)
		config.scheduler = FIFO;
	else if (strcmp(argv[8], "edf") == 0)
		config.scheduler = EDF;
	else
		error(8, NULL, NULL, NULL);
	return (config);
}
