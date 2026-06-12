/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:27:50 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/12 10:20:23 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stddef.h>

int	main(int argc, char **argv)
{
	t_config	config;
	t_moder		*moder;

	config = parser(argc, argv);
	moder = init(config);
	pthread_join(moder->thread2, NULL);
	free_all(moder);
}
