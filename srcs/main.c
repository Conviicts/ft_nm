/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:55:20 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/25 03:55:26 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	parser(t_nm *nm, int ac, char **av) {
	t_file	tmp;
	t_stat	st;
	int		fd;
	for (int i = 1; i < ac; i++) {
		if ((fd = open(av[i], 0)) == -1) {
			tmp.error = ft_strjoin("ft_nm: '", av[i]);
			tmp.error = ft_strjoin_free(tmp.error, "': No such file\n");

		}
		tmp.name = av[i];
		tmp.fd = fd;
		if (lstat(av[i], &st) > -1)
			ft_lstadd_back(&nm->files, ft_lstnew((void *)&tmp));
		else {
			tmp.error = ft_strjoin("ft_nm: ", av[i]);
			tmp.error = ft_strjoin_free(tmp.error, ": Permission denied\n");
		}
	}
}

int		main(int ac, char **av) {
	t_nm	nm;
	// t_list	*tmp;

	if (ac == 1)
		return (1);
	ft_bzero(&nm, sizeof(nm));
	parser(&nm, ac, av);

	// printf("%s\n", ((t_file *)nm.files->content)->name);
	// tmp = nm.files;
	// while (tmp) {
	// 	// if (((t_file *)tmp->content)->error) {
	// 	// 	printf("%s", ((t_file *)tmp->content)->error);
	// 	// }
	// 	tmp = tmp->next;
	// }


	return (0);
}
