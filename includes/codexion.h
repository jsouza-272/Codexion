/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:19:30 by jsouza            #+#    #+#             */
/*   Updated: 2026/05/28 10:34:09 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H
# define _DEFAULT_SOURCE

# include "types.h"
# include "utils.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

t_config	parser(int argc, char **argv);
t_table		*init(t_config c);

#endif