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

void	exit_clean(t_nm *nm, int status) {
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
		} else if (fstat(fd, &tmp->st) > -1) {
			if (S_ISDIR(tmp->st.st_mode)) {
				close(fd);
				tmp->error = ft_strjoin("ft_nm: ", av[i]);
				tmp->error = ft_strjoin_free(tmp->error, ": Is a directory\n");
			} else {
				tmp->fd = fd;
			}
		} else {
			close(fd);
			tmp->error = ft_strjoin("ft_nm: ", av[i]);
			tmp->error = ft_strjoin_free(tmp->error, ": Permission denied\n");
		}
		ft_lstadd_back(&nm->files, ft_lstnew(tmp));
	}
}

int elf32(t_file *file, char *data) {
	(void)file;
	(void)data;

	printf("ELF32\n");
	return 1;
}

int elf64(t_file *file, char *data) {
	(void)file;
	(void)data;

	printf("ELF64\n");
	return 1;
}

int		is_elf(t_file *file) {
	char	*data;

	if ((data = mmap(NULL, file->st.st_size, PROT_READ, MAP_PRIVATE, file->fd, 0)) == MAP_FAILED)
		return (0);
	if (data[0] == ELFMAG0 && data[1] == ELFMAG1 && data[2] == ELFMAG2 && data[3] == ELFMAG3) {
		data[4] == ELFCLASS32 ? elf32(file, data) : elf64(file, data);
		return (1);
	}
	if (munmap(data, file->st.st_size) < 0)
        return fprintf(stderr, "ft_nm: Warning: '%s': Unable to unmap file\n", file->name);
	return fprintf(stderr, "ft_nm: '%s': file format not recognized\n", file->name);
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
		if (((t_file *)tmp->content)->error) {
			fprintf(stderr, "%s", ((t_file *)tmp->content)->error);
		} else {
			is_elf(tmp->content);
		}
		tmp = tmp->next;
	}
	exit_clean(&nm, 0);
}
