/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsouza <jsouza@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:27:50 by jsouza            #+#    #+#             */
/*   Updated: 2026/06/02 10:33:41 by jsouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void print_config(t_config config)
{
	printf("number_of_coders: %d\n", config.number_of_coders);
	printf("time_to_burnout: %d\n", config.time_to_burnout);
	printf("time_to_compile: %d\n", config.time_to_compile);
	printf("time_to_debug: %d\n", config.time_to_debug);
	printf("time_to_refactor: %d\n", config.time_to_refactor);
	printf("number_of_compiles_required: %d\n", config.number_of_compiles_required);
	printf("dongle_cooldown: %d\n", config.dongle_cooldown);
	printf("scheduler: %c\n", config.scheduler);
}

int	main(int argc, char **argv)
{
	t_config config;
	t_moder *moder;

	config = parser(argc, argv);
	printf("PARSER END\n\n");
	moder = init(config);
	printf("INIT END\n\n");
	pthread_join(moder->thread, NULL);
	// print_config(config);
}

//void *print_config(void *tt)
//{
//	test_t *ttt;

	
//	ttt = (test_t*)tt;
//	pthread_mutex_lock(&ttt->lock);
//	if (!(ttt->config))
//		return NULL;
//	printf("number_of_coders: %d\n", (*ttt).config->number_of_coders);
//	printf("time_to_burnout: %d\n", (*ttt).config->time_to_burnout);
//	printf("time_to_compile: %d\n", (*ttt).config->time_to_compile);
//	printf("time_to_debug: %d\n", (*ttt).config->time_to_debug);
//	printf("time_to_refactor: %d\n", (*ttt).config->time_to_refactor);
//	printf("number_of_compiles_required: %d\n", (*ttt).config->number_of_compiles_required);
//	printf("dongle_cooldown: %d\n", (*ttt).config->dongle_cooldown);
//	printf("scheduler: %c\n", (*ttt).config->scheduler);
//	pthread_mutex_unlock(&ttt->lock);
//	return NULL;
//}

//int	main(int argc, char **argv)
//{
//	pthread_t t1;
//	pthread_t t2;
//	test_t ttt;

//	ttt.argc = argc;
//	ttt.argv = argv;
//	ttt.config = NULL;

//	pthread_create(&t1, NULL, parser, &ttt);
//	pthread_create(&t2, NULL, print_config, &ttt);

//	pthread_join(t1, NULL);
//	pthread_join(t2, NULL);

//}