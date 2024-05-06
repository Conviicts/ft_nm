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

void exit_clean(t_nm *nm, int status) {
	while (nm->files) {
		t_list *next = nm->files->next;
		free(((t_file *)nm->files->content)->error);
		free(nm->files->content);
		free(nm->files);
		nm->files = next;
	}
	exit(status);
}

void	parser(t_nm *nm, int ac, char **av) {
	t_file	*tmp;
	t_stat	st;
	int		fd;
	for (int i = 1; i < ac; i++) {
		if ((tmp = malloc(sizeof(t_file))) == NULL) {
			exit_clean(nm, 1);
		}
		ft_bzero(tmp, sizeof(t_file));
		tmp->name = av[i];
		if ((fd = open(av[i], O_RDONLY)) == -1) {
			tmp->error = ft_strjoin("ft_nm: '", av[i]);
			tmp->error = ft_strjoin_free(tmp->error, "': No such file\n");
		} else if (lstat(av[i], &st) == 0) {
			tmp->fd = fd;
		} else {
			close(fd);
			tmp->error = ft_strjoin("ft_nm: ", av[i]);
			tmp->error = ft_strjoin_free(tmp->error, ": Permission denied\n");
		}
		ft_lstadd_back(&nm->files, ft_lstnew(tmp));
	}
}

int		main(int ac, char **av) {
	t_nm	nm;
	t_list	*tmp;

	if (ac == 1)
		return (1);
	ft_bzero(&nm, sizeof(nm));
	parser(&nm, ac, av);

	tmp = nm.files;
	while (tmp) {
		printf("[%s]\n", ((t_file *)tmp->content)->name);
		if (((t_file *)tmp->content)->error) {
			printf("%s", ((t_file *)tmp->content)->error);
		}
		tmp = tmp->next;
	}
	exit_clean(&nm, 0);
}
