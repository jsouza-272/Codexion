/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:07:56 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/08 14:05:47 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>

typedef	struct	s_moder	t_moder;

typedef enum e_scheduler
{
	FIFO = 'f',
	EDF = 'e'
}	t_scheduler;

typedef struct s_infos
{
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
	pthread_mutex_t	moder_lock;
	pthread_cond_t	moder_cond;
	int				*ids;
	size_t			list_size;
	size_t			counter;
	int				last_id;
	int				*ids_list;
	size_t			ids_list_size;
}	t_infos;

typedef struct s_simulation
{
	int				continue_sim;
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
	t_moder			*moder;
}	t_simulation;

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
	size_t			last_use;
	size_t			dongle_cooldown;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_dongle;

typedef	struct	s_coder
{
	pthread_t	thread;
	size_t		last_compile;
	size_t		time_to_burnout;
	size_t		start;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
}	t_coder;

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
	int				table_id;
};

typedef struct s_moder
{
	pthread_t		thread;
	pthread_t		thread2;
	t_table			*tables;
	t_infos			*infos;
	t_simulation	simulation;
	size_t			current_compiles;
	size_t			nbcr;
	int				nb_coders;
	t_scheduler		scheduler;
}	t_moder;

#endif