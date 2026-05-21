/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:25:22 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/21 15:53:41 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/include.h"

int	aux_parser(char *value, int error_id)
{
	int	nb;

	nb = atoi(value);
	if (nb <= 0)
		error(error_id);
	return (nb);
}

t_config	parser(int argc, char **argv)
{
	t_config	config;

	if (argc != 9)
		error(0);
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
		error(8);
	return (config);
}
//void	*parser(void *tt)
//{
//	t_config	config;
//	test_t *ttt;

	
//	ttt = (test_t*)tt;
//	pthread_mutex_lock(&ttt->lock);
//	if ((*ttt).argc != 9)
//		error(0);
//	config.number_of_coders = aux_parser((*ttt).argv[1], 1);
//	config.time_to_burnout = aux_parser((*ttt).argv[2], 2);
//	config.time_to_compile = aux_parser((*ttt).argv[3], 3);
//	config.time_to_debug = aux_parser((*ttt).argv[4], 4);
//	config.time_to_refactor = aux_parser((*ttt).argv[5], 5);
//	config.number_of_compiles_required = aux_parser((*ttt).argv[6], 6);
//	config.dongle_cooldown = aux_parser((*ttt).argv[7], 7);
//	if (strcmp((*ttt).argv[8], "fifo") == 0)
//		config.scheduler = FIFO;
//	else if (strcmp((*ttt).argv[8], "edf") == 0)
//		config.scheduler = EDF;
//	else
//		error(8);
//	ttt->config = &config;
//	//return (config);
//	pthread_mutex_unlock(&ttt->lock);
//	return NULL;
//}
