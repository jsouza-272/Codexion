/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:12:18 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/01 13:58:25 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <sys/time.h>
# include <stdio.h>

void	error(int error_id, t_table *table, t_infos *infos);
int		get_time(void);
void	*coder_routine(void *arg);
int 	id_in_ids(int id, int *ids, size_t limit);
void	fifo(t_moder *moder);
void	edf(t_moder *moder);
void	*moder_routine(void *arg);

#endif