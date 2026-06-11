/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 11:03:13 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/11 11:35:24 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"

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

void	init_errors(int error_id, t_table *table, t_infos *infos, t_moder *moder)
{
	if (error_id == 12)
	{
		free(infos);
		error_id = 11;
	}
	if (error_id == 11)
	{
		free(table);
		error_id = 10;
	}
	if (error_id == 10)
	{
		pthread_mutex_lock(&moder->sim.lock);
		moder->sim.continue_sim = 2;
		pthread_cond_broadcast(&moder->sim.cond);
		pthread_mutex_unlock(&moder->sim.lock);
		pthread_cond_broadcast(&moder->sim.cond);
		pthread_join(moder->thread2, NULL);
		pthread_mutex_destroy(&moder->sim.lock);
		pthread_cond_destroy(&moder->sim.cond);
		free(moder);
	}
	fprintf(stderr, "Init Error\n");
}

void	error(int error_id, t_table *table, t_infos *infos, t_moder *moder)
{
	if (0 <= error_id && error_id <= 8)
		parser_error(error_id);
	else if (9 <= error_id && error_id <= 12)
		init_errors(error_id, table, infos, moder);
	exit(1);
}
