/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:19:30 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/26 14:34:52 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_scheduler
{
	FIFO = 'f',
	EDF = 'e'
}	t_scheduler;

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
	t_table		*left_table;
	t_table		*right_table;
	t_coder		coder;
	t_dongle	dongle;
};


// typedef struct test
// {
	// int argc;
	// char **argv;
	// t_config *config;
	// pthread_mutex_t lock;
// } test_t;

// void		*parser(void *tt);
t_config	parser(int argc, char **argv);
t_table		*init(t_config c);
void		error(int error_id);

#endif