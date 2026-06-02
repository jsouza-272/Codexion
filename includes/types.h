/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:07:56 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/02 10:26:52 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>

typedef enum e_scheduler
{
	FIFO = 'f',
	EDF = 'e'
}	t_scheduler;

typedef struct s_infos
{
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
	int				*ids;
	size_t			list_size;
	int				last_id;
} t_infos;

typedef struct s_simulation
{
	int continue_sim;
} t_simulation;

typedef struct s_config
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef	struct	s_dongle
{
	int	last_use;
	int	dongle_cooldown;
	pthread_mutex_t lock;
	pthread_cond_t	cond;
}	t_dongle;

typedef	struct	s_coder
{
	pthread_t	thread;
	int			last_compile;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
} t_coder;

typedef	struct	s_table	t_table;

struct	s_table
{
	t_table			*next;
	t_table			*prev;
	t_coder			coder;
	t_dongle		dongle;
	t_dongle		*right_dongle;
	t_infos			*infos;
	t_simulation	*sim;
	int 			table_id;
};

typedef struct s_moder
{
	pthread_t	thread;
	t_table *tables;
	t_infos *infos;
	t_simulation simulation;
	size_t current_compiles;
	size_t nbcr;
	int nb_coders;
	t_scheduler	scheduler;
} t_moder;

#endif